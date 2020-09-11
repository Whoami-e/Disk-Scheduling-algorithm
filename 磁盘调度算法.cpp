#include <iostream>
using namespace std;

//打印输出数组Pri
void Print(int Pri[], int x)
{
    int i;
    for (i = 0; i < x; i++)
    {
        printf("%5d", Pri[i]);
    }
}

//数组Sour把x位置的数删除，并把y前面的数向前移动，y后的数保持不变(即会出现2个y) 
void DelInq(int Sour[], int x, int y)
{
    int i;
    for (i = x; i < y; i++)
    {
        Sour[i] = Sour[i + 1];
        x++;
    }
}


void FCFS(int beginDisc,int Disc[]) {
    int DiscList[10];//存储随机生成的磁道数
    for (int i = 0; i < 10; i++) {
        DiscList[i] = Disc[i];
    }
    cout << "磁道编号为：";
    Print(DiscList, 10);
    cout << endl;
    float Aver = 0;//平均寻道长度
    int All = 0;//统计磁道移动距离之和
    int DiscNum = 9;//磁道个数
    int Temp;//计算移动的磁道距离的临时变量
    cout << "按照FCFS算法磁道的访问顺序为：";
    for (int i = 0; i < 10; i++) {
        cout << "  " << DiscList[i];
    }
    All = beginDisc - DiscList[0];
    if (All < 0)
        All = (-All);
    
    for (int i = 0; i < 9; i++) {
        Temp = DiscList[i] - DiscList[i+1];//求出移动磁道数,前一个磁道数减去后一个磁道数得出临时的移动距离
        if (Temp < 0)
            Temp = (-Temp);
        All = Temp + All;//求全部磁道数的总和 
        /*DelInq(DiscList, 0,DiscNum);
        DiscNum--;*/
    }
    cout << endl;
    Aver = ((float)All) / 10;
    cout << "磁道移动距离之和：" << All << endl;
    cout << "平均寻道长度：" << Aver << endl;
}

//最短寻道时间优先算法(SSTF)
void SSTF(int beginDisc,int Disc[]) {
    int DiscList[10];//存储随机生成的磁道数
    int DiscList1[10];//存放已排序好的磁道编号（结果）
    for (int i = 0; i < 10; i++) {
        DiscList[i] = Disc[i];
    }
    cout << "磁道编号为：";
    Print(DiscList, 10);
    cout << endl;
    int All, min, mid, index, tag[100] = { 0 };//tag的值为1和0,1表示已操作
    float Aver = 0;//平均寻道长度
    All = 0;
    for (int j = 0; j < 10; j++) {
        min = 9999;
        for (int i = 0; i < 10; i++)
            if (tag[i] == 0) {
                mid = abs(beginDisc - DiscList[i]);
                if (min > mid) {
                    min = mid;
                    index = i;
                }
            }
        All += min;
        tag[index] = 1;
        DiscList1[j] = DiscList[index];
        beginDisc = DiscList[index];
    }
    cout << "按照FCFS算法磁道的访问顺序为：";
    for (int i = 0; i < 10; i++) {
        cout << "  " << DiscList1[i];
    }
    cout << endl;
    Aver = ((float)All) / 10;
    cout << "磁道移动距离之和：" << All << endl;
    cout << "平均寻道长度：" << Aver << endl;
}

//扫描算法(SCAN)
void SCAN(int beginDisc,int Disc[]) {
    int DiscList[10];//存储随机生成的磁道数
    float Aver = 0,Aver1 = 0;//平均寻道长度
    int All = 0,All1 = 0;//统计磁道移动距离之和
    for (int i = 0; i < 10; i++) {
        DiscList[i] = Disc[i];
    }
    cout << "磁道编号为：";
    Print(DiscList, 10);
    cout << endl << endl;
    //冒泡排序
    int nTemp = 0;
    for (int i = 0; i < 10; ++i)
    {
        for (int j = i; j < 10; ++j)
        {
            if (DiscList[i] > DiscList[j])
            {
                nTemp = DiscList[i];
                DiscList[i] = DiscList[j];
                DiscList[j] = nTemp;
            }
        }
    }
    
    //当初始磁头位置在所有要访问的磁道中比最大的还大时
    if (DiscList[9] <= beginDisc) {
        cout << "按照SCAN算法磁道的访问顺序为：";
        for (int i = 9; i >= 0; i--) {
            cout << "  " << DiscList[i];
        }
        All = beginDisc - DiscList[0];
        cout << endl << endl;
        Aver = ((float)All) / 10;
        cout << "磁道移动距离之和：" << All << endl << endl;
        cout << "平均寻道长度：" << Aver << endl << endl;
    }
    else
    {
        //当初始磁头位置在所有要访问的磁道中比最小的还小时
        if (beginDisc <= DiscList[0]) {
            cout << "按照SCAN算法磁道的访问顺序为：";
            for (int i = 0; i < 10; i++) {
                cout << "  " << DiscList[i];
            }
            All = DiscList[9] - beginDisc;
            cout << endl << endl;
            Aver = ((float)All) / 10;
            cout << "磁道移动距离之和：" << All << endl << endl;
            cout << "平均寻道长度：" << Aver << endl << endl;
        }
        else
        {   //当初始磁道在所要访问的所有磁道中间某个位置时

            int k = 0;
            while (DiscList[k]<beginDisc)//确定初始磁道的位置
            {
                k++;
            }
            int l = k-1;
            int r = k;

            //向内
            cout << "按照SCAN算法磁道的访问顺序为（向内）：";
            for (int i = l; i >= 0; i--) {
                cout << "  " << DiscList[i];
            }
            for (int i = r; i < 10; i++) {
                cout << "  " << DiscList[i];
            }
            All = beginDisc - 2 * DiscList[0] + DiscList[9];
            Aver = ((float)All) / 10;
            cout << endl;
            cout << "向内移动时磁道移动距离之和：" << All << endl;
            cout << "向内移动时平均寻道长度：" << Aver << endl << endl;
            //向外
            cout << "按照SCAN算法磁道的访问顺序为（向外）：";
            for (int i = r; i < 10; i++) {
                cout << "  " << DiscList[i];
            }
            for (int i = l; i >= 0; i--)
            {
                cout << "  " << DiscList[i];
            }
            All1 = 2 * DiscList[9] - beginDisc - DiscList[0];     
            cout << endl;
            Aver1 = ((float)All1) / 10;
            cout << "向外移动时磁道移动距离之和：" << All1 << endl;
            cout << "向外移动时平均寻道长度：" << Aver1 << endl << endl;
        }
    }
    
}

//循环扫描算法(CSCAN)
void CSCAN(int beginDisc,int Disc[]) {
    int DiscList[10];//存储随机生成的磁道数
    float Aver = 0,Aver1 = 0;//平均寻道长度
    int All = 0, All1 = 0;//统计磁道移动距离之和
    for (int i = 0; i < 10; i++) {
        DiscList[i] = Disc[i];
    }
    cout << "磁道编号为：";
    Print(DiscList, 10);
    cout << endl << endl;
    //冒泡排序
    int nTemp = 0;
    for (int i = 0; i < 10; ++i)
    {
        for (int j = i; j < 10; ++j)
        {
            if (DiscList[i] > DiscList[j])
            {
                nTemp = DiscList[i];
                DiscList[i] = DiscList[j];
                DiscList[j] = nTemp;
            }
        }
    }

    if (DiscList[9] <= beginDisc) {//当初始磁头位置在所有要访问的磁道中比最大的还大时
        cout << "按照CSCAN算法磁道的访问顺序为：";
        for (int i = 0;i < 10;i++)
        {
            cout << " " << DiscList[i];
        }
        All = beginDisc - 2 * DiscList[0] + DiscList[9];
    }
    else
    {
        if (beginDisc <= DiscList[0]) {//当初始磁头位置在所有要访问的磁道中比最小的还小时
            cout << "按照CSCAN算法磁道的访问顺序为：";
            for (int i = 0; i < 10; i++)
            {
                cout << " " << DiscList[i];
            }
            All = DiscList[9] - beginDisc;
        }
        else
        {
            int k = 0;
            while (DiscList[k]<beginDisc)//确定初始磁道的位置
            {
                k++;
            }
            int l = k-1;
            int r = k;

            //向内
            cout << "按照CSCAN算法磁道的访问顺序为（向内）：";
            for (int i = l; i >= 0; i--) {
                cout << "  " << DiscList[i];
            }
            for (int i = 9; i >= r; i--) {
                cout << "  " << DiscList[i];
            }
            All = 2 * DiscList[9] + beginDisc - 2 * DiscList[0] - DiscList[r];
            Aver = ((float)All) / 10;
            cout << endl;
            cout << "向内移动时磁道移动距离之和：" << All << endl;
            cout << "向内移动时平均寻道长度：" << Aver << endl << endl;
            //向外
            cout << "按照CSCAN算法磁道的访问顺序为（向外）：";
            for (int i = r; i < 10; i++) {
                cout << "  " << DiscList[i];
            }
            for (int i = 0; i < r; i++)
            {
                cout << "  " << DiscList[i];
            }
            All1 = 2 * DiscList[9] - beginDisc - 2 * DiscList[0] + DiscList[l];
            cout << endl;
            Aver1 = ((float)All1) / 10;
            cout << "向外移动时磁道移动距离之和：" << All1 << endl;
            cout << "向外移动时平均寻道长度：" << Aver1 << endl << endl;

        }
    }
}
int main()
{
    int i;
    int beginDisc;//初始磁道编号
    int n;
    int Disc[10];
    cout << "请输入初始磁道编号：";
    cin >> beginDisc;
    cout << endl;
    cout << "请输入10个磁道编号（输入的顺序代表磁道到来的顺序）：";
    for (int i = 0; i < 10; i++) {
        cin >> Disc[i];
    }

    cout << endl << endl;
    cout << "********************FCFS********************" << endl;
    FCFS(beginDisc,Disc);
    cout << endl;
    cout << "********************SSTF********************" << endl;
    SSTF(beginDisc, Disc);
    cout << endl;
    cout << "********************SCAN********************" << endl;
    SCAN(beginDisc, Disc);
    cout << endl;
    cout << "********************CSCAN********************" << endl;
    CSCAN(beginDisc, Disc);
    cout << endl;
}


