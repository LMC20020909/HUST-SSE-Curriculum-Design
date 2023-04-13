/*********在静态语义正确的情况下生成中间代码，否则程序可能崩溃*****************/
#include "def.h"
void error(int Line,int Colum,string errMsg);
#define YYSTYPE int   //此行是为了包含parser.tab.hpp不引起错误而加,可以在后面使用相关常量
#include "parser.tab.hpp"

string NewTemp()
{
    static int num=0;
    return "Temp_"+to_string(++num);
}

string NewLabel()
{
    static int num=0;
    return "Label_"+to_string(++num);
}

map <int,string> Instruction={{LABEL,"LABEL "},{FUNCTION,"FUNCTION  "},{ASSIGN,":="},{PLUS,"+"},{UPLUS,"+"},
                    {MINUS,"-"},{UMINUS,"-"},{DPLUS, "++"}, {DMINUS, "--"}, {PLUSD, "++"}, {MINUSD, "--"}, 
                    {STAR,"*"},{DIV,"/"},{GOTO,"  GOTO  "},
                    {GT,">"},{GE,">="},{LT,"<"},{LE,"<="},{EQ,"=="},{NE,"!="},
                    {JGT,">"},{JGE,">="},{JLT,"<"},{JLE,"<="},{JEQ,"=="},{JNE,"!="},
                    {RETURN,"  RETURN  "},{ARG,"  ARG  "},{PARAM,"  PARAM  "}};

void DisplayIR(list <IRCode> IRCodes)
{
    for(auto a:IRCodes)
    {
        string OpnStr1,OpnStr2=a.Opn2.Name,ResultStr=a.Result.Name;
        if (a.Opn1.Name==string("_CONST"))
            switch (a.Opn1.Type)
            {
                case T_CHAR: OpnStr1=string("#")+to_string(a.Opn1.constCHAR);break;
                case T_INT:  OpnStr1=string("#")+to_string(a.Opn1.constINT);break;
                case T_FLOAT:OpnStr1=string("#")+to_string(a.Opn1.constFLOAT);break;
            }
        else OpnStr1=a.Opn1.Name;

        switch (a.Op) {
            case ASSIGN: cout<<"  "<<ResultStr<<" := "<<OpnStr1<<endl; break;
            case UPLUS: case UMINUS:
                         cout<<"  "<<ResultStr<<" := "<<Instruction[a.Op]<<" "<<OpnStr1<<endl; break;
            case PLUS:  case MINUS:  case STAR:   case DIV:
            case LE:  case LT:   case GE: case GT:  case EQ:  case NE:
                         cout<<"  "<<ResultStr<<":= "<<OpnStr1<<Instruction[a.Op]<<OpnStr2<<endl; break;
            case JLE:  case JLT:   case JGE: case JGT:  case JEQ:  case JNE:
                         cout<<"  "<<"IF "<<OpnStr1<<Instruction[a.Op]<<OpnStr2<<" GOTO "<<ResultStr<<endl;break;
            case DPLUS: case DMINUS:
                         cout<<"  "<<ResultStr<<":= "<<Instruction[a.Op]<<OpnStr1<<endl;break;
            case PLUSD: case MINUSD:
                         cout<<"  "<<ResultStr<<":= "<<OpnStr1<<Instruction[a.Op]<<endl;break;
            case GOTO: case PARAM: case ARG: case RETURN:
                         cout<<Instruction[a.Op]<<ResultStr<<endl; break;
            case FUNCTION:case LABEL:
                         cout<<Instruction[a.Op]<<ResultStr<<":"<<endl; break;
            case CALL:   cout<<"  "<<ResultStr<<" := "<<"CALL "<<OpnStr1<<endl; break;
            case CALL0:  cout<<"  CALL "<<OpnStr1<<endl; break;
            case ARRLOAD:
                         cout<<"  "<<ResultStr<<":="<<OpnStr1<<"["<<OpnStr2<<"]"<<endl; break;
            case ARRASSIGN:
                         cout<<"  "<<ResultStr<<"["<<OpnStr1<<"]"<<":="<<OpnStr2<<endl; break;
            case END:    cout<<"  End Of Program"<<endl;break;
        }
    }
}
void GenObject(list <IRCode> IRCodes);

void DisplaySymbolTable(SymbolStackDef *SYM);

void ProgAST::GenIR()
{
    for(auto a:ExtDefs)     //将各外部项代码依次连接
    {
        a->GenIR();
        list <IRCode>::iterator it=IRCodes.end();
        IRCodes.splice(it,a->IRCodes);
    }
    DisplayIR(IRCodes);
    GenObject(IRCodes);
//    DisplaySymbolTable(&SymbolStack);
}

void ExtVarDefAST::GenIR()  //外部变量定义
{ /*由于未考虑全局变量的初始化，所以无中间代码*/ }


void VarDecAST::GenIR()
{//有初始化表达式，需要生成中间代码
    if (!Exp) return;
    Opn Result(VarDefPtr->Alias,VarDefPtr->Type,VarDefPtr->Offset,VarDefPtr->isGolbal);
    int TempVarOffset=0;
    Opn Opn1=Exp->GenIR(TempVarOffset);
    list <IRCode> ::iterator it=IRCodes.end();
    IRCodes.splice(it,Exp->IRCodes);
    IRCodes.push_back(IRCode(ASSIGN,Opn1,Opn(),Result));
}
void DefAST::GenIR()
{
    list <IRCode>::iterator it;
    for(auto a:LocVars)
    {
        a->GenIR();
        it=IRCodes.end();
        IRCodes.splice(it,a->IRCodes);
    }
}

void BasicTypeAST::GenIR()
{
}

void FuncDefAST::GenIR()
{
    if(Body) {
        for(auto a:Params)
            IRCodes.push_back(IRCode(PARAM,Opn(),Opn(),Opn(a->ParamName->Name,0,0,0))); //(PARAM,,,形参名)

        MaxVarSize=FuncDefPtr->ARSize;
        Body->GenIR("", "", "");
        list <IRCode>::iterator it=IRCodes.end();
        IRCodes.splice(it,Body->IRCodes);            //连接函数体语句中间代码
        FuncDefPtr->ARSize+=MaxTempVarOffset;        //函数AR(栈帧)的大小
        IRCode IRFunc=IRCode(FUNCTION,Opn(),Opn(),Opn(Name,0,0,0));
        if (Name==string("main"))
        {
            IRFunc.Result.Offset=FuncDefPtr->ARSize; //主函数的栈帧大小
            IRCodes.push_back(IRCode(END,Opn(),Opn(),Opn()));  //添加程序结束标记
        }
        IRCodes.push_front(IRFunc);                             //函数开始(FUNCTION,,,Name)
    }
}
void ParamAST::GenIR(){}

void CompStmAST::GenIR(string lableCase, string lableBreak, string lableContinue)
{
    list <IRCode>::iterator it;
    for(auto a:Decls)
    {
        a->GenIR();
        it=IRCodes.end();
        IRCodes.splice(it,a->IRCodes);
    }
    for(auto a:Stms)
    {
        a->GenIR("", lableBreak, lableContinue);
        it=IRCodes.end();
        IRCodes.splice(it,a->IRCodes);
    }
}

void ExprStmAST::GenIR(string lableCase, string lableBreak, string lableContinue)
{
    int TempVarOffset=0;
//    if (typeid(*Exp)==typeid(FuncCallAST) && ((FuncCallAST *)Exp)->FuncRef->Type==T_VOID)
//        cout<<"无参函数的语句"<<((FuncCallAST *)Exp)->FuncRef->Name<<endl;
    Exp->GenIR(TempVarOffset);
    if (TempVarOffset>MaxTempVarOffset)
        MaxTempVarOffset=TempVarOffset;
    list <IRCode>::iterator it=IRCodes.end();
    IRCodes.splice(it,Exp->IRCodes);
}
void IfStmAST::GenIR(string lableCase, string lableBreak, string lableContinue)
{
    string LabelThen=NewLabel();
    string LabelEnd=NewLabel();

    /*计算条件表达式，后面这条件判断处理可以将修改成短路语句的形式，即将标号LabelThen
      和LabelEnd带入，但表达式一旦能得到真假结果，后续不需要计算，直接转移到目标位置。
      而不是下面把整个条件表达式计算完成后，再根据结果确定转移位置*/
    int TempVarOffset=0;
    Cond->GenIR(TempVarOffset,LabelThen,LabelEnd);     //计算条件表达式
    ThenStm->GenIR("", lableBreak, lableContinue);

    list <IRCode>::iterator it=IRCodes.end();
    IRCodes.splice(it,Cond->IRCodes);
    IRCodes.push_back(IRCode(LABEL,Opn(),Opn(),Opn(LabelThen,0,0,0)));//if子句前的标号
    it=IRCodes.end();
    IRCodes.splice(it,ThenStm->IRCodes);
    IRCodes.push_back(IRCode(LABEL,Opn(),Opn(),Opn(LabelEnd,0,0,0))); //if语句出口标号

}
void IfElseStmAST::GenIR(string lableCase, string lableBreak, string lableContinue)
{
    string LabelThen=NewLabel();
    string LabelElse=NewLabel();
    string LabelEnd=NewLabel();

    int TempVarOffset=0;
    Cond->GenIR(TempVarOffset,LabelThen,LabelElse);
    ThenStm->GenIR("", lableBreak, lableContinue);
    ElseStm->GenIR("", lableBreak, lableContinue);

    list <IRCode>::iterator it=IRCodes.end();
    IRCodes.splice(it,Cond->IRCodes);
    IRCodes.push_back(IRCode(LABEL,Opn(),Opn(),Opn(LabelThen,0,0,0)));//if子句前的标号
    it=IRCodes.end();
    IRCodes.splice(it,ThenStm->IRCodes);
    IRCodes.push_back(IRCode(GOTO,Opn(),Opn(),Opn(LabelEnd,0,0,0)));
    IRCodes.push_back(IRCode(LABEL,Opn(),Opn(),Opn(LabelElse,0,0,0)));//else子句前的标号
    it=IRCodes.end();
    IRCodes.splice(it,ElseStm->IRCodes);
    IRCodes.push_back(IRCode(LABEL,Opn(),Opn(),Opn(LabelEnd,0,0,0))); //if语句出口标号

}
void WhileStmAST::GenIR(string lableCase, string lableBreak, string lableContinue)
{
    string LoopCond=NewLabel();
    string LoopEntry=NewLabel();
    string LoopEnd=NewLabel();

    int TempVarOffset=0;
    Cond->GenIR(TempVarOffset,LoopEntry,LoopEnd);     //计算条件表达式
    Body->GenIR("", LoopEnd, LoopCond);

    IRCodes.push_back(IRCode(LABEL,Opn(),Opn(),Opn(LoopCond,0,0,0)));
    list <IRCode>::iterator it=IRCodes.end();
    IRCodes.splice(it,Cond->IRCodes);
    IRCodes.push_back(IRCode(LABEL,Opn(),Opn(),Opn(LoopEntry,0,0,0)));//循环入口标号
    it=IRCodes.end();
    IRCodes.splice(it,Body->IRCodes);
    IRCodes.push_back(IRCode(GOTO,Opn(),Opn(),Opn(LoopCond,0,0,0))); //结束本次循环，转去重新计算循环条件
    IRCodes.push_back(IRCode(LABEL,Opn(),Opn(),Opn(LoopEnd,0,0,0))); //循环结束标号
}
void ForStmAST::GenIR(string lableCase, string lableBreak, string lableContinue)
{
    string LoopCond=NewLabel();
    string LoopEntry=NewLabel();
    string LoopEnd=NewLabel();
    string LoopContinue=NewLabel();

    int TempVarOffset=0;
    SinExp->GenIR(TempVarOffset);
    Cond->GenIR(TempVarOffset,LoopEntry,LoopEnd);     //计算条件表达式
    EndExp->GenIR(TempVarOffset);
    Body->GenIR("", LoopEnd, LoopContinue);

    list <IRCode>::iterator it=IRCodes.end();
    IRCodes.splice(it,SinExp->IRCodes);
    IRCodes.push_back(IRCode(LABEL,Opn(),Opn(),Opn(LoopCond,0,0,0)));
    it=IRCodes.end();
    IRCodes.splice(it,Cond->IRCodes);
    IRCodes.push_back(IRCode(LABEL,Opn(),Opn(),Opn(LoopEntry,0,0,0)));//循环入口标号
    it=IRCodes.end();
    IRCodes.splice(it,Body->IRCodes);
    IRCodes.push_back(IRCode(LABEL,Opn(),Opn(),Opn(LoopContinue,0,0,0))); 
    it=IRCodes.end();
    IRCodes.splice(it,EndExp->IRCodes);
    IRCodes.push_back(IRCode(GOTO,Opn(),Opn(),Opn(LoopCond,0,0,0))); //结束本次循环，转去重新计算循环条件
    IRCodes.push_back(IRCode(LABEL,Opn(),Opn(),Opn(LoopEnd,0,0,0))); //循环结束标号
}
void CaseStmAST::GenIR(string lableCase, string lableBreak, string lableContinue)
{
    list <IRCode> ::iterator it=IRCodes.end();
    IRCodes.push_back(IRCode(LABEL,Opn(),Opn(),Opn(lableCase,0,0,0))); //循环结束标号
    for(auto a:Body)
    {
        a->GenIR("", lableBreak, lableContinue);
        it=IRCodes.end();
        IRCodes.splice(it,a->IRCodes);
    }
}
void SwitchStmAST::GenIR(string lableCase, string lableBreak, string lableContinue)
{
    string SwitchEnd=NewLabel();
    string SwitchDefault;
    int TempVarOffset=0;
    Opn Result = Exp->GenIR(TempVarOffset);
    list <IRCode> ::iterator it=IRCodes.end();
    IRCodes.splice(it,Exp->IRCodes);

    for(auto a:Cases) {
        Opn KeyValue("_CONST",T_INT,0,0);KeyValue.constINT=(((ConstAST *)(a->Cond))->ConstVal).constINT;
        string caseLable=NewLabel();
        IRCodes.push_back(IRCode(JEQ,Result,KeyValue,Opn(caseLable,0,0,0)));
        a->GenIR(caseLable, SwitchEnd, lableContinue);
    }
    if(containDefault) {
        SwitchDefault=NewLabel();
        IRCodes.push_back(IRCode(GOTO,Opn(),Opn(),Opn(SwitchDefault,0,0,0)));
    }

    for(auto a:Cases) {
        it=IRCodes.end();
        IRCodes.splice(it,a->IRCodes);
    }
    if(containDefault) {
        IRCodes.push_back(IRCode(LABEL,Opn(),Opn(),Opn(SwitchDefault,0,0,0)));
        for(auto a:Default)
        {
            a->GenIR("", SwitchEnd, lableContinue);
            it=IRCodes.end();
            IRCodes.splice(it,a->IRCodes);
        }
    }
    IRCodes.push_back(IRCode(LABEL,Opn(),Opn(),Opn(SwitchEnd,0,0,0)));
}
void ReturnStmAST::GenIR(string lableCase, string lableBreak, string lableContinue)
{
    if (!Exp) return;
    int TempVarOffset=0;
    Opn Result=Exp->GenIR(TempVarOffset);
    list <IRCode> ::iterator it=IRCodes.end();
    IRCodes.splice(it,Exp->IRCodes);
    IRCodes.push_back(IRCode(RETURN,Opn(),Opn(),Result));
}
void BreakStmAST::GenIR(string lableCase, string lableBreak, string lableContinue)
{
    IRCodes.push_back(IRCode(GOTO,Opn(),Opn(),Opn(lableBreak,0,0,0)));
}
void ContinueStmAST::GenIR(string lableCase, string lableBreak, string lableContinue)
{
    IRCodes.push_back(IRCode(GOTO,Opn(),Opn(),Opn(lableContinue,0,0,0)));
}

/**************表达式的中间代码生成************************/
Opn VarAST::GenIR(int &TempVarOffset)
{
    //通过语义检查后，VarRef指向对应表项，否则为空，程序会崩溃
    if(VarRef->Kind == 'V' || VarRef->Kind == 'P') 
    {
        Opn VarOpn(VarRef->Alias,VarRef->Type,VarRef->Offset, VarRef->isGolbal);
        return VarOpn;
    }
    else if(VarRef->Kind == 'A')
    {
        list <IRCode> ::iterator it=IRCodes.end();
        Opn Result=index[0]->GenIR(TempVarOffset);
        it=IRCodes.end();
        IRCodes.splice(it,index[0]->IRCodes);
        for(int i=1;i<index.size();i++) 
        {
            Opn DimValue(NewTemp(),T_INT,TempVarOffset+MaxVarSize,0); //生成临时变量保存常量值
            TempVarOffset+=TypeWidth[T_INT];           //修改临时变量的偏移量
            if (TempVarOffset>MaxTempVarOffset)
                MaxTempVarOffset=TempVarOffset;
            Opn Opn1("_CONST",T_INT,0,0);             //别名或临时变量名为_CONST时，表示常量
            Opn1.constINT=VarRef->Dims[i];
            IRCodes.push_back(IRCode(ASSIGN,Opn1,Opn(),DimValue));

            Opn MultiResult(NewTemp(),T_INT,TempVarOffset+MaxVarSize,0); //生成临时变量保存运算结果，结果类型应该根据运算结果来定
            TempVarOffset+=TypeWidth[T_INT];           //这里只是简单处理成和左右操作数类型相同，修改临时变量的偏移量
            if (TempVarOffset>MaxTempVarOffset)
                MaxTempVarOffset=TempVarOffset;
            IRCodes.push_back(IRCode(STAR,Result,DimValue,MultiResult));

            Opn IndexValue=index[i]->GenIR(TempVarOffset);
            it=IRCodes.end();
            IRCodes.splice(it,index[i]->IRCodes);

            Opn AddResult(NewTemp(),T_INT,TempVarOffset+MaxVarSize,0); //生成临时变量保存运算结果，结果类型应该根据运算结果来定
            TempVarOffset+=TypeWidth[T_INT];           //这里只是简单处理成和左右操作数类型相同，修改临时变量的偏移量
            if (TempVarOffset>MaxTempVarOffset)
                MaxTempVarOffset=TempVarOffset;
            IRCodes.push_back(IRCode(PLUS,MultiResult,IndexValue,AddResult));

            Result=AddResult;
        }

        Opn TypeValue(NewTemp(),T_INT,TempVarOffset+MaxVarSize,0); //生成临时变量保存常量值
        TempVarOffset+=TypeWidth[T_INT];           //修改临时变量的偏移量
        if (TempVarOffset>MaxTempVarOffset)
            MaxTempVarOffset=TempVarOffset;
        Opn Opn2("_CONST",T_INT,0,0);             //别名或临时变量名为_CONST时，表示常量
        Opn2.constINT=TypeWidth[VarRef->Type];
        IRCodes.push_back(IRCode(ASSIGN,Opn2,Opn(),TypeValue));

        Opn OffsetResult(NewTemp(),T_INT,TempVarOffset+MaxVarSize,0); //生成临时变量保存运算结果，结果类型应该根据运算结果来定
        TempVarOffset+=TypeWidth[T_INT];           //这里只是简单处理成和左右操作数类型相同，修改临时变量的偏移量
        if (TempVarOffset>MaxTempVarOffset)
            MaxTempVarOffset=TempVarOffset;
        IRCodes.push_back(IRCode(STAR,Result,TypeValue,OffsetResult));

        Opn LoadEnd(NewTemp(),VarRef->Type,TempVarOffset+MaxVarSize,0); //生成临时变量保存常量值
        TempVarOffset+=TypeWidth[VarRef->Type];           //修改临时变量的偏移量
        if (TempVarOffset>MaxTempVarOffset)
            MaxTempVarOffset=TempVarOffset;

        Opn Arr(VarRef->Alias, VarRef->Type, VarRef->Offset, VarRef->isGolbal);

        IRCodes.push_back(IRCode(ARRLOAD,Arr,OffsetResult,LoadEnd));

        return LoadEnd;
    }
}

void VarAST::GenIR(int &TempVarOffset,string LabelTrue,string LabelFalse)
{
    //根据变量的值确定转移方向
    Opn Result=GenIR(TempVarOffset);
    Opn Zero("_CONST",T_INT,0,0);Zero.constINT=0;
    IRCodes.push_back(IRCode(JNE,Result,Zero,Opn(LabelTrue,0,0,0)));
    IRCodes.push_back(IRCode(GOTO,Opn(),Opn(),Opn(LabelFalse,0,0,0)));
}

Opn ConstAST::GenIR(int &TempVarOffset)
{
    //将常量赋值给生成的临时变量
    Opn Result(NewTemp(),Type,TempVarOffset+MaxVarSize,0); //生成临时变量保存常量值
    TempVarOffset+=TypeWidth[Type];           //修改临时变量的偏移量
    if (TempVarOffset>MaxTempVarOffset)
        MaxTempVarOffset=TempVarOffset;
    Opn Opn1("_CONST",Type,0,0);             //别名或临时变量名为_CONST时，表示常量
    Opn1.constCHAR=ConstVal.constCHAR;
    Opn1.constINT=ConstVal.constINT;
    Opn1.constFLOAT=ConstVal.constFLOAT;                //按最大长度的成员进行整体复制

    IRCodes.push_back(IRCode(ASSIGN,Opn1,Opn(),Result));
    return Result;

}

void ConstAST::GenIR(int &TempVarOffset,string LabelTrue,string LabelFalse)
{
    Opn Result=GenIR(TempVarOffset);
    Opn Zero("_CONST",T_INT,0,0);Zero.constINT=0;
    IRCodes.push_back(IRCode(JNE,Result,Zero,Opn(LabelTrue,0,0,0)));
    IRCodes.push_back(IRCode(GOTO,Opn(),Opn(),Opn(LabelFalse,0,0,0)));
}


Opn AssignAST::GenIR(int &TempVarOffset)
{
    if(((VarAST *)LeftValExp)->VarRef->Kind!='A') {
        Opn Result=LeftValExp->GenIR(TempVarOffset);
        Opn Opn1=RightValExp->GenIR(TempVarOffset);

        list <IRCode> ::iterator it=IRCodes.end();
        IRCodes.splice(it,LeftValExp->IRCodes);
        it=IRCodes.end();
        IRCodes.splice(it,RightValExp->IRCodes);
        IRCodes.push_back(IRCode(ASSIGN,Opn1,Opn(),Result));
        return Result;
    }
    else 
    {
        list <IRCode> ::iterator it=IRCodes.end();
        Opn Result=((VarAST *)LeftValExp)->index[0]->GenIR(TempVarOffset);
        it=IRCodes.end();
        IRCodes.splice(it,((VarAST *)LeftValExp)->index[0]->IRCodes);
        for(int i=1;i<((VarAST *)LeftValExp)->index.size();i++) 
        {
            Opn DimValue(NewTemp(),T_INT,TempVarOffset+MaxVarSize,0); //生成临时变量保存常量值
            TempVarOffset+=TypeWidth[T_INT];           //修改临时变量的偏移量
            if (TempVarOffset>MaxTempVarOffset)
                MaxTempVarOffset=TempVarOffset;
            Opn Opn1("_CONST",T_INT,0,0);             //别名或临时变量名为_CONST时，表示常量
            Opn1.constINT=((VarAST *)LeftValExp)->VarRef->Dims[i];
            IRCodes.push_back(IRCode(ASSIGN,Opn1,Opn(),DimValue));

            Opn MultiResult(NewTemp(),T_INT,TempVarOffset+MaxVarSize,0); //生成临时变量保存运算结果，结果类型应该根据运算结果来定
            TempVarOffset+=TypeWidth[T_INT];           //这里只是简单处理成和左右操作数类型相同，修改临时变量的偏移量
            if (TempVarOffset>MaxTempVarOffset)
                MaxTempVarOffset=TempVarOffset;
            IRCodes.push_back(IRCode(STAR,Result,DimValue,MultiResult));

            Opn IndexValue=((VarAST *)LeftValExp)->index[i]->GenIR(TempVarOffset);
            it=IRCodes.end();
            IRCodes.splice(it,((VarAST *)LeftValExp)->index[i]->IRCodes);

            Opn AddResult(NewTemp(),T_INT,TempVarOffset+MaxVarSize,0); //生成临时变量保存运算结果，结果类型应该根据运算结果来定
            TempVarOffset+=TypeWidth[T_INT];           //这里只是简单处理成和左右操作数类型相同，修改临时变量的偏移量
            if (TempVarOffset>MaxTempVarOffset)
                MaxTempVarOffset=TempVarOffset;
            IRCodes.push_back(IRCode(PLUS,MultiResult,IndexValue,AddResult));

            Result=AddResult;
        }

        Opn TypeValue(NewTemp(),T_INT,TempVarOffset+MaxVarSize,0); //生成临时变量保存常量值
        TempVarOffset+=TypeWidth[T_INT];           //修改临时变量的偏移量
        if (TempVarOffset>MaxTempVarOffset)
            MaxTempVarOffset=TempVarOffset;
        Opn Opn2("_CONST",T_INT,0,0);             //别名或临时变量名为_CONST时，表示常量
        Opn2.constINT=TypeWidth[((VarAST *)LeftValExp)->VarRef->Type];
        IRCodes.push_back(IRCode(ASSIGN,Opn2,Opn(),TypeValue));

        Opn OffsetResult(NewTemp(),T_INT,TempVarOffset+MaxVarSize,0); //生成临时变量保存运算结果，结果类型应该根据运算结果来定
        TempVarOffset+=TypeWidth[T_INT];           //这里只是简单处理成和左右操作数类型相同，修改临时变量的偏移量
        if (TempVarOffset>MaxTempVarOffset)
            MaxTempVarOffset=TempVarOffset;
        IRCodes.push_back(IRCode(STAR,Result,TypeValue,OffsetResult));

        Opn LoadEnd(NewTemp(),((VarAST *)LeftValExp)->VarRef->Type,TempVarOffset+MaxVarSize,0); //生成临时变量保存常量值
        TempVarOffset+=TypeWidth[((VarAST *)LeftValExp)->VarRef->Type];           //修改临时变量的偏移量
        if (TempVarOffset>MaxTempVarOffset)
            MaxTempVarOffset=TempVarOffset;

        Opn Arr(((VarAST *)LeftValExp)->VarRef->Alias, ((VarAST *)LeftValExp)->VarRef->Type, ((VarAST *)LeftValExp)->VarRef->Offset, ((VarAST *)LeftValExp)->VarRef->isGolbal);

        Opn OpnRight=RightValExp->GenIR(TempVarOffset);
        it=IRCodes.end();
        IRCodes.splice(it,RightValExp->IRCodes);

        IRCodes.push_back(IRCode(ARRASSIGN,OffsetResult,OpnRight,Arr));

        return OpnRight;
    }
}

void AssignAST::GenIR(int &TempVarOffset,string LabelTrue,string LabelFalse)
{
    //根据左值表达式的值确定转移方向
    Opn Result=GenIR(TempVarOffset);
    Opn Zero("_CONST",T_INT,0,0);Zero.constINT=0;
    IRCodes.push_back(IRCode(JNE,Result,Zero,Opn(LabelTrue,0,0,0)));
    IRCodes.push_back(IRCode(GOTO,Opn(),Opn(),Opn(LabelFalse,0,0,0)));
}


Opn BinaryExprAST::GenIR(int &TempVarOffset)
{
    Opn Opn1=LeftExp->GenIR(TempVarOffset);
    Opn Opn2=RightExp->GenIR(TempVarOffset);
    Opn Result(NewTemp(),Opn1.Type,TempVarOffset+MaxVarSize,0); //生成临时变量保存运算结果，结果类型应该根据运算结果来定
    TempVarOffset+=TypeWidth[Opn1.Type];           //这里只是简单处理成和左右操作数类型相同，修改临时变量的偏移量
    if (TempVarOffset>MaxTempVarOffset)
            MaxTempVarOffset=TempVarOffset;

    list <IRCode> ::iterator it=IRCodes.end();
    IRCodes.splice(it,LeftExp->IRCodes);
    it=IRCodes.end();
    IRCodes.splice(it,RightExp->IRCodes);
    IRCodes.push_back(IRCode(Op,Opn1,Opn2,Result));
    return Result;
}

void BinaryExprAST::GenIR(int &TempVarOffset,string LabelTrue,string LabelFalse)
{
    list <IRCode> ::iterator it;
    switch (Op)
    {
        case AND: case OR:
            {
            string Label=NewLabel();
            if (Op==AND) LeftExp->GenIR(TempVarOffset,Label,LabelFalse);
            else LeftExp->GenIR(TempVarOffset,LabelTrue,Label);
            RightExp->GenIR(TempVarOffset,LabelTrue,LabelFalse);
            list <IRCode> ::iterator it=IRCodes.end();
            IRCodes.splice(it,LeftExp->IRCodes);
            
            IRCodes.push_back(IRCode(LABEL,Opn(),Opn(),Opn(Label,0,0,0)));
            it=IRCodes.end();
            IRCodes.splice(it,RightExp->IRCodes);
            }
            break;
        case PLUS:  case MINUS:  case STAR:  case  DIV:    case MOD:
            {
            Opn Result=GenIR(TempVarOffset);
            Opn Zero("_CONST",T_INT,0,0);Zero.constINT=0;
            IRCodes.push_back(IRCode(JNE,Result,Zero,Opn(LabelTrue,0,0,0)));
            IRCodes.push_back(IRCode(GOTO,Opn(),Opn(),Opn(LabelFalse,0,0,0)));
            }
            break;
        default:     //处理关系运算符
            Opn Opn1=LeftExp->GenIR(TempVarOffset);
            Opn Opn2=RightExp->GenIR(TempVarOffset);
            it=IRCodes.end();
            IRCodes.splice(it,LeftExp->IRCodes);
            it=IRCodes.end();
            IRCodes.splice(it,RightExp->IRCodes);
            IRCode IR(JGT,Opn1,Opn2,Opn(LabelTrue,0,0,0));
            if (Op==GE) IR.Op=JGE;
            else if (Op==LT) IR.Op=JLT;
            else if (Op==LE) IR.Op=JLE;
            else if (Op==EQ) IR.Op=JEQ;
            else if (Op==NE) IR.Op=JNE;
            IRCodes.push_back(IR);
            IRCodes.push_back(IRCode(GOTO,Opn(),Opn(),Opn(LabelFalse,0,0,0)));
    }
}

Opn UnaryExprAST::GenIR(int &TempVarOffset)
{
    Opn Opn1=Exp->GenIR(TempVarOffset);
    Opn Result(NewTemp(),Exp->Type,TempVarOffset+MaxVarSize,0);
    TempVarOffset+=TypeWidth[Exp->Type];
    if (TempVarOffset>MaxTempVarOffset)
        MaxTempVarOffset=TempVarOffset;

    list <IRCode> ::iterator it=IRCodes.end();
    IRCodes.splice(it,Exp->IRCodes);
    IRCodes.push_back(IRCode(Op,Opn1,Opn(),Result));
    return Result;
}

void UnaryExprAST::GenIR(int &TempVarOffset,string LabelTrue,string LabelFalse)
{
    //Exp->GenIR(TempVarOffset,LabelFalse,LabelTrue);
    //list <IRCode> ::iterator it=IRCodes.end();
    //IRCodes.splice(it,Exp->IRCodes);
    Opn Result=GenIR(TempVarOffset);
    Opn Zero("_CONST",T_INT,0,0);Zero.constINT=0;
    IRCodes.push_back(IRCode(JNE,Result,Zero,Opn(LabelTrue,0,0,0)));
    IRCodes.push_back(IRCode(GOTO,Opn(),Opn(),Opn(LabelFalse,0,0,0)));
}


Opn FuncCallAST::GenIR(int &TempVarOffset)
{
    list <IRCode> ARGS;
    list <IRCode> ::iterator it;
    Opn Opn1,Result;
    SymbolsInAScope *ParamPtr=FuncRef->ParamPtr;
    int i=0;
    for(auto a:Params)
    {
        if (Name!=string("write"))  //write函数特殊处理，参数传递用的寄存器
        {   //用Opn1的Offset保存形参的偏移量,方便目标代码参数传递,将实参值保存在AR中
            VarSymbol *Sym=(VarSymbol*)((ParamPtr->Symbols).at(i++));
            Opn1.Offset=Sym->Offset;
        }
        Result=a->GenIR(TempVarOffset);        //计算实参表达式的值
        it=IRCodes.end();
        IRCodes.splice(it,a->IRCodes);
        ARGS.push_back(IRCode(ARG,Opn1,Opn(),Result));
    }
    it=IRCodes.end();
    IRCodes.splice(it,ARGS);
    Opn1.Name=Name;
    Opn1.Type=FuncRef->Type;
    Opn1.SymPtr=FuncRef;
    if (FuncRef->Type!=T_VOID)
    {
        Result=Opn(NewTemp(),FuncRef->Type,TempVarOffset+MaxVarSize,0);//临时变量保存返回结果
        TempVarOffset+=TypeWidth[FuncRef->Type];
        if (TempVarOffset>MaxTempVarOffset)
            MaxTempVarOffset=TempVarOffset;
        IRCodes.push_back(IRCode(CALL,Opn1,Opn(),Result));
    }
    else IRCodes.push_back(IRCode(CALL0,Opn1,Opn(),Opn())); //返回值为void
    return Result;
}


void FuncCallAST::GenIR(int &TempVarOffset,string LabelTrue,string LabelFalse)
{
    Opn Result=GenIR(TempVarOffset);
    Opn Zero("_CONST",T_INT,0,0);Zero.constINT=0;
    IRCodes.push_back(IRCode(JNE,Result,Zero,Opn(LabelTrue,0,0,0)));
    IRCodes.push_back(IRCode(GOTO,Opn(),Opn(),Opn(LabelFalse,0,0,0)));
}
