package com.oyoungy;


import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.PriorityQueue;

/**
 * 分支定界法求0-1背包问题
 */
public class Knapsack {

    private double[][] items;    //商品，包含编号 重量 价值 重量价值比
    private double weight;       //背包大小
    private double maxValue=0;   //最大价值
    private Node maxNode;        //最大价值情况下的取法

    Knapsack()
    {
        maxNode = new Node();
    }


    public double getMaxValue() {
        return maxValue;
    }

    /**
     * 加载文件
     * @param filename
     * @throws IOException
     */
    public void loadItem(String filename) throws IOException {
        Path path = Paths.get(filename);
        List<String> lines = Files.readAllLines(path);
        items = new double[lines.size()-1][4];
        int j=0;
        for(String line:lines)
        {
            String[] item = line.split("\\s+");
            if(item.length==1)
            {
                weight = Double.parseDouble(item[0]);
            }
            else {
                for (int i = 0; i < item.length; i++) {
                    items[j][i] = Double.parseDouble(item[i]);
                }
                j++;
            }
        }
        Arrays.sort(items, new Comparator<double[]>() {
            @Override
            public int compare(double[] o1, double[] o2) {
                if(o1[3]<o2[3]) return 1;
                else if (o1[3]>o2[3]) return -1;
                else return 0;
            }
        });
    }

    /**
     * 定界函数
     * @param node
     * @return
     */
    public double upBound(Node node)
    {
        if(weight>node.w) {
            if (node.level < items.length)
                node.bound = node.v + (weight - node.w) * items[node.level][3];
            else if (node.level == items.length) {
                node.bound = node.v;
                //node.level-=1;
            }
        }
        return node.bound;
    }

    /**
     * 分支定界算法
     */
    public void brandchAndBoundKnap()
    {
        //上界越大的优先权越大
        PriorityQueue<Node> queue = new PriorityQueue<>(new Comparator<Node>() {
            @Override
            public int compare(Node o1, Node o2) {
                if(o1.bound<o2.bound) return 1;
                else if (o1.bound>o2.bound) return -1;
                return 0;
            }
        });
        int index = 0;
        Node n = new Node(0, 0, 1, 0, items.length);
        upBound(n);
        queue.add(n);
        while (!queue.isEmpty())
        {
            Node node = queue.poll();
            if(maxValue<node.bound)
            {
                //包含当前节点
                for(int i=0; i<2; i++)
                {
                    Node n1 = node.clone();
                    if(i==0)  //表示当前物品放入背包中
                    {
                        n1.w+=items[n1.level][1];
                        n1.v+=items[n1.level][2];
                        n1.selected[n1.level] = (int)items[n1.level][0];
                    }
                    n1.level+=1;
                    upBound(n1);
                    if(n1.w<weight&&n1.v!=n1.bound)
                    {
                        queue.add(n1);
                    }
                    else if(n1.v==n1.bound)
                    {
                        if(maxValue<n1.bound)
                        {
                            maxValue = n1.bound;
                            maxNode = n1.clone();
                        }
                    }
                }
            }
            else
            {
                return;
            }
        }
    }

    public static void main(String[] args) throws IOException {
        Knapsack knapsack = new Knapsack();
        knapsack.loadItem("src/main/resources/kna.txt");
        knapsack.brandchAndBoundKnap();
        Node node = knapsack.maxNode;
        for(int i=0; i<node.selected.length; i++)
        {
            System.out.print(node.selected[i]+ " ");
        }
        System.out.println();
        System.out.println(knapsack.getMaxValue());
    }
}