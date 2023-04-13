#include "def.h"
#include <fstream>
#define YYSTYPE int   //������Ϊ�˰���parser.tab.hpp������������,�����ں���ʹ����س���
#include "parser.tab.hpp"

void GenObject(list <IRCode> IRCodes)
{
    fstream ObjectFile;
    ObjectFile.open("ObjectFile.s",ios::out);

    /*Ԥ�ȸ���read��write��Ŀ�����*/
    ObjectFile<<".data\n";
    ObjectFile<<"_Prompt: .asciiz \"Enter an integer:  \"\n";
    ObjectFile<<"_ret: .asciiz \"\\n\"\n";
    ObjectFile<<".globl main\n";
    ObjectFile<<".text\n\n";
    ObjectFile<<"read:\n";
    ObjectFile<<"  li $v0,4\n";
    ObjectFile<<"  la $a0,_Prompt\n";
    ObjectFile<<"  syscall\n";
    ObjectFile<<"  li $v0,5\n";
    ObjectFile<<"  syscall\n";
    ObjectFile<<"  jr $ra\n\n";
    ObjectFile<<"write:\n";
    ObjectFile<<"  li $v0,1\n";
    ObjectFile<<"  syscall\n";
    ObjectFile<<"  li $v0,4\n";
    ObjectFile<<"  la $a0,_ret\n";
    ObjectFile<<"  syscall\n";
    ObjectFile<<"  move $v0,$0\n";
    ObjectFile<<"  jr $ra\n";

    for(list <IRCode>::iterator it=IRCodes.begin();it!=IRCodes.end();it++)
    {
      switch (it->Op)
        {
            case ASSIGN:
                if (it->Opn1.Name==string("_CONST"))  //����ֻ������������
                    ObjectFile<< "  li $t1, "<<it->Opn1.constINT<<endl;
                else       //����ֻ�����˼򵥱�������������Ҫ����
                    ObjectFile<< "  lw $t1, "<<it->Opn1.Offset<<"($sp)"<<endl;
                ObjectFile<< "  sw $t1,  "<<it->Result.Offset<<"($sp)"<<endl;
                break;
            case PLUS:
            case MINUS:
            case STAR:
            case DIV:
                 ObjectFile<< "  lw $t1, "<<it->Opn1.Offset<<"($sp)"<<endl;
                 ObjectFile<< "  lw $t2, "<<it->Opn2.Offset<<"($sp)"<<endl;
                 if (it->Op==PLUS)       ObjectFile<< "  add $t3,$t1,$t2"<<endl;
                 else if (it->Op==MINUS) ObjectFile<< "  sub $t3,$t1,$t2"<<endl;
                 else if (it->Op==STAR)  ObjectFile<< "  mul $t3,$t1,$t2"<<endl;
                 else  {
                            ObjectFile<< "  div $t1, $t2"<<endl;
                            ObjectFile<< "  mflo $t3"<<endl;
                        }
                 ObjectFile<< "  sw $t3, "<<it->Result.Offset<<"($sp)"<<endl;
                 break;

            case RETURN:
                ObjectFile<< "  lw $v0,"<<it->Result.Offset<<"($sp)"<<endl; //����ֵ�͵�$v0
                ObjectFile<< "  jr $ra"<<endl;
                break;

            case FUNCTION:
                ObjectFile<< "\n"<<it->Result.Name<<":\n";
                if (it->Result.Name==string("main")) //���⴦��main
                    ObjectFile<< "  addi $sp, $sp, -"<<it->Result.Offset<<endl;
                break;
            case PARAM: break; //ֱ����������һ��
            case ARG:   break; //ֱ����������һ��,ֱ���������ã���ͷ��ȡʵ��ֵ�����͵��βε�Ԫ��
            case LABEL: ObjectFile<<it->Result.Name<<":"<<endl;  break;
            case GOTO:  ObjectFile<< "  j "<<it->Result.Name<<endl;  break;
            case END:
                ObjectFile<<"  li $v0,10\n  syscall"<<endl;
                break;
            case JLE:
            case JLT:
            case JGE:
            case JGT:
            case JEQ:
            case JNE:
                ObjectFile<< "  lw $t1, "<<it->Opn1.Offset<<"($sp)"<<endl;
                ObjectFile<< "  lw $t2, "<<it->Opn2.Offset<<"($sp)"<<endl;
                if (it->Op==JLE)      ObjectFile<< "  ble $t1,$t2,"<<it->Result.Name<<endl;
                else if (it->Op==JLT) ObjectFile<< "  blt $t1,$t2,"<<it->Result.Name<<endl;
                else if (it->Op==JGE) ObjectFile<< "  bge $t1,$t2,"<<it->Result.Name<<endl;
                else if (it->Op==JGT) ObjectFile<< "  bgt $t1,$t2,"<<it->Result.Name<<endl;
                else if (it->Op==JEQ)  ObjectFile<< "  beq $t1,$t2,"<<it->Result.Name<<endl;
                else                  ObjectFile<< "  bne $t1,$t2,"<<it->Result.Name<<endl;
                break;

            case CALL:  case CALL0:
                list <IRCode>::iterator it0=it; it0--;  //it0ָ��ǰ����ܵ�ARG
                if (it->Opn1.Name==string("read"))//���⴦��read
                {
                    ObjectFile<< "  addi $sp, $sp, -4\n";
                    ObjectFile<< "  sw $ra,0($sp)\n";      //�������ص�ַ
                    ObjectFile<< "  jal read\n";           //�������ص�ַ
                    ObjectFile<< "  lw $ra,0($sp)\n";      //�ָ����ص�ַ
                    ObjectFile<< "  addi $sp, $sp, 4\n";
                    ObjectFile<< "  sw $v0, "<<it->Result.Offset<<"($sp)\n";
                    break;
                }
                if (it->Opn1.Name==string("write"))//���⴦��write
                {
                    ObjectFile<< "  lw $a0, "<<it0->Result.Offset<<"($sp)\n";  //ǰ��ARG��ƫ����
                    ObjectFile<< "  addi $sp, $sp, -4\n";
                    ObjectFile<< "  sw $ra,0($sp)\n";
                    ObjectFile<< "  jal write\n";
                    ObjectFile<< "  lw $ra,0($sp)\n";
                    ObjectFile<< "  addi $sp, $sp, 4\n";
                    break;
                }
                ObjectFile<< "  move $t0,$sp"<<endl; //���浱ǰ������sp��$t0�У�Ϊ��ȡʵ�α��ʽ��ֵ


                ObjectFile<< "  addi $sp, $sp, -"<<static_cast <FuncSymbol *>(it->Opn1.SymPtr)->ARSize<<endl;  //�����¼�ռ�
                ObjectFile<< "  sw $ra,0($sp)"<<endl;                      //�������ص�ַ
                while (it0->Op==ARG)                       //����ȡ����ֵ���ݵ��βε�Ԫ��
                {
                    //��ԭջ֡��ƫ��it0->Result.Offset����ȡ�����͵���ջ֡��it0->Opn1.Offset
                    ObjectFile<< "  lw $t1, "<<it0->Result.Offset<<"($t0)"<<endl; //ȡʵ��ֵ��$t1��
                    ObjectFile<< "  sw $t1,"<<it0->Opn1.Offset<<"($sp)"<<endl;    //�͵������ú������βε�Ԫ
                    it0--;
                }
                ObjectFile<<"  jal "<<it->Opn1.Name<<endl;      //��ת�������ú���
                ObjectFile<<"  lw $ra,0($sp)"<<endl;            //�ָ����ص�ַ
                ObjectFile<<"  addi $sp,$sp,"<<((FuncSymbol *)(it->Opn1.SymPtr))->ARSize<<endl; //�ͷŻ��¼�ռ�
                ObjectFile<<"  sw $v0,"<<it->Result.Offset<<"($sp)"<<endl;  //ȡ����ֵ,��void����������Ҫȡֵ
                break;
        }
    }
    ObjectFile.close();
}
