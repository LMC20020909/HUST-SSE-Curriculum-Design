import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
from sklearn.cluster import KMeans
from tslearn.clustering import TimeSeriesKMeans
from sklearn.decomposition import PCA
from sklearn.cluster import DBSCAN
from sklearn.preprocessing import StandardScaler


def draw_plot():
    data = pd.read_excel("库存数据.xlsx")
    print(data.shape)
    x = data.loc[:, "hours"]
    name_y = ["A", "B", "C", "D", "E", "F"]
    plt.figure(figsize=(30, 15))
    for i in range(1, 7):
        plt.subplot(2, 3, i)
        plt.ylim(-80, 800)
        plt.plot(x, data.iloc[:, i], 'o', markersize=3)
        coeff = np.polyfit(x, data.iloc[:, i], 10)
        f = np.poly1d(coeff)
        plt.plot(x, f(x), linewidth=3.0)
        plt.xlabel("hours")
        plt.ylabel(name_y[i - 1])
    plt.suptitle("Changes of the six items' inventory over time", y=0.92, fontsize=15)
    plt.show()


def draw_hist():
    data = pd.read_excel("库存数据.xlsx")
    print(data.shape)
    x = data.loc[:, "hours"]
    name_y = ["A", "B", "C", "D", "E", "F"]
    plt.figure(figsize=(30, 15))
    for i in range(1, 7):
        plt.subplot(2, 3, i)
        # plt.ylim(-80, 800)
        # plt.plot(x, data.iloc[:, i], 'o', markersize=3)
        # coeff = np.polyfit(x, data.iloc[:, i], 10)
        # f = np.poly1d(coeff)
        # plt.plot(x, f(x), linewidth=3.0)
        color = ["#5975a4", "#cc8963", "#5f9e6e", "#b55d60", "#857aab", "#8d7866"]
        y = data.iloc[:, i]
        # weights = np.ones_like(y) / float(len(y))
        plt.hist(y, color=color[0], rwidth=0.8, label='histogram', bins=10, density=True)
        sns.kdeplot(y, label='density plot', color=color[1], linewidth=3.0, shade=True)
        plt.xlabel("number of item")
        plt.ylabel("frequency")
        plt.title("item_"+name_y[i-1])
        plt.legend()
    plt.suptitle("Inventory distribution of six items", y=0.95, fontsize=15)
    plt.show()


def draw_box():
    data = pd.read_excel("库存数据.xlsx")
    print(data.shape)
    name_y = ["A", "B", "C", "D", "E", "F"]
    plt.figure(figsize=(15, 7))
    for i in range(1, 7):
        plt.subplot(2, 3, i)
        plt.subplots_adjust(hspace=0.5, wspace=0.5)
        y = data.iloc[:, i]
        sns.violinplot(x=name_y[i-1], data=data, palette='Blues')
        # sns.swarmplot(x=name_y[i-1], data=data)
    plt.show()


def kmeans():
    data = pd.read_excel('库存数据.xlsx')

    # 假设数据存储在CSV文件中，文件名为inventory.csv
    # data = pd.read_csv('inventory.csv')

    # 提取物品的库存量数据，并转置，使每种物品的库存量成为一个数据点
    items_data = data.iloc[:, 1:].T

    # 选择聚类数量，例如 2
    num_clusters = 3

    # 初始化 KMeans 模型
    kmeans = KMeans(n_clusters=num_clusters, random_state=0)

    # 对数据进行聚类
    kmeans.fit(items_data)

    # 得到聚类结果
    labels = kmeans.labels_

    # 使用主成分分析（PCA）降维以便于可视化
    pca = PCA(n_components=2)
    items_data_pca = pca.fit_transform(items_data)

    # 创建一个可视化图
    fig, ax = plt.subplots()

    # 为每个聚类绘制散点图
    for cluster_id in range(num_clusters):
        cluster_data = items_data_pca[labels == cluster_id]
        ax.scatter(cluster_data[:, 0], cluster_data[:, 1], label=f'Cluster {cluster_id}', s=120)
    # 设置图例和轴标签
    ax.legend()
    ax.set_xlabel('PCA Component 1')
    ax.set_ylabel('PCA Component 2')

    # 为每个数据点添加物品标签
    item_labels = ['A', 'B', 'C', 'D', 'E', 'F']
    for i, item_label in enumerate(item_labels):
        ax.annotate(item_label, (items_data_pca[i, 0], items_data_pca[i, 1]))

    plt.title("Result of k-means", fontsize=15)
    # 显示图形
    plt.show()


def kmeans2():
    data = pd.read_excel('库存数据.xlsx')

    # 提取物品的库存量数据，并转置，使每种物品的库存量成为一个数据点
    items_data = data.iloc[:, 1:].T

    # 选择聚类数量，例如 2
    num_clusters = 3

    # 初始化 KMeans 模型
    kmeans = KMeans(n_clusters=num_clusters, random_state=0)

    # 对数据进行聚类
    kmeans.fit(items_data)

    # 得到聚类结果
    labels = kmeans.labels_

    # 创建一个可视化图
    fig, ax = plt.subplots()

    # 设置条形图的宽度
    bar_width = 0.35

    # 为每个聚类绘制条形图
    for cluster_id in range(num_clusters):
        cluster_data = items_data[labels == cluster_id]
        bar_positions = np.arange(cluster_data.shape[0]) + cluster_id * bar_width
        ax.bar(bar_positions, cluster_data.mean(axis=1), width=bar_width, label=f'Cluster {cluster_id}')

    # 设置图例和轴标签
    ax.legend()
    ax.set_xlabel('Items')
    ax.set_ylabel('Average Inventory')

    # 为每个数据点添加物品标签
    item_labels = ['A', 'B', 'C', 'D', 'E', 'F']
    ax.set_xticks(np.arange(len(item_labels)) + bar_width / 2)
    ax.set_xticklabels(item_labels)

    # 显示图形
    plt.show()


def dbscan():
    data = pd.read_excel('库存数据.xlsx')

    # 提取物品的库存量数据，并转置，使每种物品的库存量成为一个数据点
    items_data = data.iloc[:, 1:].T

    # 对数据进行标准化
    scaler = StandardScaler()
    scaled_data = scaler.fit_transform(items_data)

    # 初始化 DBSCAN 模型
    # 调整 eps 和 min_samples 参数以获得合适的聚类结果
    dbscan = DBSCAN(eps=25, min_samples=1)

    # 对数据进行聚类
    dbscan.fit(scaled_data)

    # 得到聚类结果
    labels = dbscan.labels_

    # 使用 PCA 将数据降至二维
    pca = PCA(n_components=2)
    reduced_data = pca.fit_transform(scaled_data)

    # 创建一个可视化图
    fig, ax = plt.subplots()

    # 获取聚类数量（排除噪声点）
    num_clusters = len(set(labels)) - (1 if -1 in labels else 0)

    # 为每个聚类绘制散点图并添加物品标签
    item_labels = ['A', 'B', 'C', 'D', 'E', 'F']
    for cluster_id in range(num_clusters):
        cluster_data = reduced_data[labels == cluster_id]
        ax.scatter(cluster_data[:, 0], cluster_data[:, 1], label=f'Cluster {cluster_id}', s=120)
        for point, label in zip(cluster_data, np.array(item_labels)[labels == cluster_id]):
            ax.annotate(label, (point[0], point[1]), textcoords="offset points", xytext=(0, 5), ha='center')

    # 如果存在噪声点，将其绘制到图上并添加物品标签
    if -1 in labels:
        noise_data = reduced_data[labels == -1]
        ax.scatter(noise_data[:, 0], noise_data[:, 1], label='Noise')
        for point, label in zip(noise_data, np.array(item_labels)[labels == -1]):
            ax.annotate(label, (point[0], point[1]), textcoords="offset points", xytext=(0, 5), ha='center')

    # 设置图例和轴标签
    ax.legend()
    ax.set_xlabel('PCA Component 1')
    ax.set_ylabel('PCA Component 2')

    # 显示图形
    plt.title("Result of DBSCAN", fontsize=15)
    plt.show()


def dbscan2():
    data = pd.read_excel('库存数据.xlsx')
    # 提取物品的库存量数据，并转置，使每种物品的库存量成为一个数据点
    items_data = data.iloc[:, 1:].T

    # 对数据进行标准化
    scaler = StandardScaler()
    scaled_data = scaler.fit_transform(items_data)

    # 初始化 DBSCAN 模型
    # eps 是密度半径，需要根据数据特点进行调整
    # min_samples 是每个簇中的最小数据点数，这里我们设置为 2
    dbscan = DBSCAN(eps=25, min_samples=1)

    # 对数据进行聚类
    dbscan.fit(scaled_data)

    # 得到聚类结果
    labels = dbscan.labels_

    # 创建一个可视化图
    fig, ax = plt.subplots()

    # 设置条形图的宽度
    bar_width = 0.35

    # 获取聚类数量（排除噪声点）
    num_clusters = len(set(labels)) - (1 if -1 in labels else 0)

    # 为每个聚类绘制条形图
    for cluster_id in range(num_clusters):
        cluster_data = items_data[labels == cluster_id]
        bar_positions = np.arange(cluster_data.shape[0]) + cluster_id * bar_width
        ax.bar(bar_positions, cluster_data.mean(axis=1), width=bar_width, label=f'Cluster {cluster_id}')

    # 如果存在噪声点，将其绘制到图上
    if -1 in labels:
        noise_data = items_data[labels == -1]
        bar_positions = np.arange(noise_data.shape[0]) + num_clusters * bar_width
        ax.bar(bar_positions, noise_data.mean(axis=1), width=bar_width, label='Noise')

    # 设置图例和轴标签
    ax.legend()
    ax.set_xlabel('Items')
    ax.set_ylabel('Average Inventory')

    # 为每个数据点添加物品标签
    item_labels = ['A', 'B', 'C', 'D', 'E', 'F']
    ax.set_xticks(np.arange(len(item_labels)) + bar_width / 2)
    ax.set_xticklabels(item_labels)

    # 显示图形
    plt.show()

if __name__ == "__main__":
    # draw_hist()
    # data = pd.read_excel("库存数据.xlsx")
    # pd.set_option('display.max_rows', None)  # 显示全部行
    # pd.set_option('display.max_columns', None)  # 显示全部列
    # print(data.describe())
    # draw_box()
    # kmeans()
    # kmeans2()
    dbscan()
    # dbscan2()