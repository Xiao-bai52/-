#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
#include<string.h>
#include<Windows.h>
#define LEN sizeof(struct student)
#define FORMAT1 "----------------------------------------------------------------------------------------\n"
#define FORMAT2 "|      学号     |   姓名   |   班级   |   高数  |  英语  |   C语言  |   总分  |   排名 | \n"
#define FORMAT3 "|---------------|----------|----------|---------|--------|----------|---------|--------|\n"
int k = 1;      /****引入全局变量控制菜单和主函数****/
int r = 0;      /****引入全局变量记录录入信息的个数****/

/******************定义学生成绩结构体************************/
struct student
{
    char num[30];       /*学号*/
    char name[15];      /*姓名*/
    char classes[15];   /*班级*/
    float clanguage;    /*C语言成绩*/
    float math;         /*高数成绩*/
    float english;      /*英语成绩*/
    float sum;          /*总分*/
    int rank;           /*排名*/
};
struct student stu[100];    /*定义全局结构体数组，存储上述信息*/

/*********************函数声明与简介*************************/
void printheader();     /*打印函数*/
void file();            /*调用存储文件函数*/
void menu();            /*程序主菜单*/
void input();           /*录入学生成绩信息*/
void search();          /*查找学生信息*/
void modify();          /*修改学生成绩信息*/
void rank();            /*辅助排序函数*/
void sort();            /*排序学生成绩*/
void tongji();          /*统计学生成绩*/
void show();            /*显示学生基本信息*/
void del();             /*删除学生成绩信息*/


/*******************用于打印表格的函数***********************/
void printheader()
{
    printf(FORMAT1);
    printf(FORMAT2);
    printf(FORMAT3);
}

/*******************调用存储文件的函数***********************/
void file()
{
    int m = 0;
    int i = 0;
    FILE* fp;       /*定义文件指针fp，便于对文件进行操作*/
    if ((fp = fopen("stuData.txt", "a+")) == NULL)                             /*打开指定文件*/
    {
        printf("打开文件失败\n");
        return;
    }
    while (!feof(fp))                /*当没有运行到文件尾部时*/
    {
        if (fread(&stu[m], LEN, 1, fp) == 1)                       /*读取文件中的记录*/
        {
            m++;
            r = m;
        }
    }
    fclose(fp);
    if ((fp = fopen("stuData.txt", "wb")) == NULL)            /*打开文件用于记录信息*/
    {
        printf("打开文件失败\n");
        return;
    }
    for (i = 0; i < m; i++)
    {
        fwrite(&stu[i], LEN, 1, fp);  /*向指定的磁盘文件写入信息*/
    }
    fclose(fp);
}

/******************学生成绩管理系统菜单**********************/
void menu()
{
    printf("\t\t\t学生成绩管理系统\t\n");
    printf("     ◤■■■■■■■■■■▼▼▼▼▼▼▼▼■■■■■■■■■■◥\n");
    printf("\t\t|\t 0. 系统帮助\t\t\t|\n");
    printf("\t\t|\t 1. 录入学生成绩\t\t|\n");
    printf("\t\t|\t 2. 查找学生成绩\t\t|\n");
    printf("\t\t|\t 3. 修改学生成绩\t\t|\n");
    printf("\t\t|\t 4. 学生成绩排序\t\t|\n");
    printf("\t\t|\t 5. 学生成绩统计\t\t|\n");
    printf("\t\t|\t 6. 显示学生成绩\t\t|\n");
    printf("\t\t|\t 7. 删除学生成绩\t\t|\n");
    printf("\t\t|\t 8. 退出系统\t\t\t|\n");
    printf("     ◣■■■■■■■■■■▲▲▲▲▲▲▲▲■■■■■■■■■■◢\n");
    printf("\t\t\t请输入您的操作<0-8>:\n");
    system("color 6");
    char choice = _getch();
    switch (choice)
    {
    case '0':
        system("cls");
        printf("\t\t\t\t----------【系统帮助】----------\n");
        printf("\t\t\t\t1. 本系统最多录入100名学生的成绩\n");
        printf("\t\t\t\t2. 本系统可删除或修改学生的成绩\n");
        printf("\t\t\t\t3. 请按照系统的提示进行操作\n");
        printf("\t\t\t\t4. 感谢使用\n");
        printf("\t\t\t\t--------------------------------\n");
        printf("\t\t\t\t------(按任意键返回主菜单)------\n");
        int x;
        x = _getch();
        if (x)
        {
            system("cls");
            return;
        }
        break;
    case '1':
        system("cls");
        printf("----------【录入学生成绩】----------\n");
        input();
        break;
    case '2':
        system("cls");
        printf("\t\t\t\t------【查找学生成绩】------\n");
        search();
        break;
    case '3':
        system("cls");
        printf("\t\t\t    ----------【修改学生成绩】----------\n");
        modify();
        break;
    case '4':
        system("cls");
        printf("\t\t\t\t------------【学生成绩排序】------------\n");
        sort();
        break;
    case '5':
        system("cls");
        printf("\t\t\t     ----------------------【学生成绩统计】----------------------\n");
        tongji();
        break;
    case '6':
        system("cls");
        printf("----------【显示学生成绩】----------\n");
        show();
        break;
    case '7':
        system("cls");
        printf("\t\t\t        --------【删除学生成绩】--------\n");
        del();
        break;
    case '8':
        k = 0;
        system("cls");
        printf("按任意键可正常退出,感谢您的使用！\n");
        system("pause");
        exit(0);
        break;
    default:
        printf("选择错误,请重新输入");
        system("cls");
        break;
    }
}


/**********************录入学生成绩信息**********************/
void input()
{
    int i, m = 0;    /*变量m表示信息或者说记录的条数*/
    char ch[2];
    FILE* fp;       /*定义文件指针fp，便于对文件进行操作*/
    if ((fp = fopen("stuData.txt", "a+")) == NULL)                             /*打开指定文件*/
    {
        printf("打开文件失败\n");
        return;
    }
    while (!feof(fp))                /*当没有运行到文件尾部时*/
    {
        if (fread(&stu[m], LEN, 1, fp) == 1)                       /*读取文件中的记录*/
        {
            m++;
            r = m;
        }
    }
    fclose(fp);                     /*关闭文件指针fp所指向的文件*/
    if (m == 0)
        printf("暂时没有学生数据!\n");
    else
    {
        printf("已有%d位学生信息\n", m);
    }
    if ((fp = fopen("stuData.txt", "wb")) == NULL)            /*打开文件用于记录信息*/
    {
        printf("打开文件失败\n");
        return;
    }
    for (i = 0; i < m; i++)
    {
        fwrite(&stu[i], LEN, 1, fp);  /*向指定的磁盘文件写入信息*/
    }
    printf("是否要录入学生成绩(y/n):");
    scanf("%s", ch);
    while (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)                /*判断是否要录入新信息*/
    {
        printf("请输入学号:");
        scanf("%s", stu[m].num);   /*输入学生学号*/
        for (i = 0; i < m; i++)
            if (strcmp(stu[m].num, stu[i].num) == 0) /*从第一个记录开始判断，是否和第m个记录的学号一样*/
            {
                printf("此学号已存在！按任意键返回至主菜单！");
                _getch();
                system("cls");
                fclose(fp);
                return;
            }
        /*如果学号可用，则继续输入其它数据*/
        printf("请输入姓名(同名学生请区分）:");
        scanf("%s", stu[m].name);/*输入学生姓名*/
        printf("请输入班级:");
        scanf("%s", stu[m].classes);    /*输入班级*/
        printf("请输入C语言成绩:");
        scanf("%f", &stu[m].clanguage);      /*输入C语言成绩*/
        printf("请输入高数成绩:");
        scanf("%f", &stu[m].math);       /*输入高数课成绩*/
        printf("请输入英语成绩:");
        scanf("%f", &stu[m].english);      /*输入英语课成绩*/
        stu[m].sum = stu[m].clanguage + stu[m].math + stu[m].english; /*计算出总成绩*/
        printf("总成绩:%.1f\n", stu[m].sum);
        if (fwrite(&stu[m], LEN, 1, fp) != 1) /*将新录入的信息写入指定的磁盘文件*/
        {
            printf("保存失败!");
            _getch();
        }
        else
        {
            printf("%s 的成绩已保存!\n", stu[m].name);
            m++;
            r = m;
        }
        printf("是否继续录入成绩?(y/n):");   /*询问是否继续*/
        scanf("%s", ch);
        printf("\n");
    }
    fclose(fp);
    printf("操作成功!\n");
    system("cls");
}

/**********************查找学生成绩信息**********************/
void search()
{
    file();
    struct student* p;
    char nums[30];
    int s;
    int item;
    int flag;
    char name[20];
    printf("\t\t\t\t----------------------------\n");
    printf("\t\t\t\t--------1.按学号查询--------\n");
    printf("\t\t\t\t--------2.按姓名查询--------\n");
    printf("\t\t\t\t--------3.返回主菜单--------\n");
    printf("\t\t\t\t----------------------------\n");
    printf("\t\t\t\t------请在子菜单中选择------\n");
    rank();
    while (1)
    {
        char item = _getch();
        flag = 0;//flag用于判断学号或姓名是否存在
        switch (item)
        {
        case '1':
            printf("请输入要查询的学号：");
            scanf("%s", nums);
            for (s = 0; s < r; s++)
                if (strcmp(stu[s].num, nums) == 0)
                {
                    flag = 1;
                    printheader();
                    p = stu + s;
                    printf("|%15s|%10s|%10s|%9.1f|%8.1f|%10.1f|%9.1f|%8d|\n", p->num, p->name, p->classes, p->math, p->english, p->clanguage, p->sum, p->rank);
                    printf(FORMAT1);
                    printf("\n");
                    printf("您可继续从子菜单中选择：\n");
                }
            if (0 == flag)
            {
                printf("学号不存在！\n\n");
                printf("您可继续从子菜单中选择：\n");
            }
            break;
        case '2':
            printf("请输入要查询的姓名:");
            scanf("%s", name);
            for (s = 0; s < r; s++)
                if (strcmp(stu[s].name, name) == 0)
                {
                    flag = 1;
                    printheader();
                    p = stu + s;
                    printf("|%15s|%10s|%10s|%9.1f|%8.1f|%10.1f|%9.1f|%8d|\n", p->num, p->name, p->classes, p->math, p->english, p->clanguage, p->sum, p->rank);
                    printf(FORMAT1);
                    printf("\n");
                    printf("您可继续从子菜单中选择：\n");
                }
            if (0 == flag)
            {
                printf("该姓名不存在\n\n");
                printf("您可继续从子菜单中选择\n");
            }
            break;
        case '3':
            system("cls");
            return;
        default:
            printf("无效选择，请在1-3中选择\n");
        }
    }
}

/**********************修改学生成绩信息**********************/
void modify()
{

    struct student* p;
    char nums[30];
    int item;//用于控制对主菜单的选择
    int flag;
    char names[20];
    int s;
    printf("\t\t\t    ------------------------------------\n");
    printf("\t\t\t    ------------1.按学号修改------------\n");
    printf("\t\t\t    ------------2.按姓名修改------------\n");
    printf("\t\t\t    ------------3.返回主菜单------------\n");
    printf("\t\t\t    ------------------------------------\n");
    printf("\t\t\t    ----------请在子菜单中选择----------\n");
    while (1)
    {
        int i, m = 0;    /*变量m表示信息或者说记录的条数*/
        FILE* fp;       /*定义文件指针fp，便于对文件进行操作*/
        if ((fp = fopen("stuData.txt", "a+")) == NULL)                             /*打开指定文件*/
        {
            printf("打开文件失败\n");
            return;
        }
        while (!feof(fp))                /*当没有运行到文件尾部时*/
        {
            if (fread(&stu[m], LEN, 1, fp) == 1)                       /*读取文件中的记录*/
            {
                m++;
                r = m;
            }
        }
        fclose(fp);
        if ((fp = fopen("stuData.txt", "wb")) == NULL)            /*打开文件用于记录信息*/
        {
            printf("打开文件失败\n");
            return;
        }
        rank();
        char item = _getch();
        flag = 0;//flag用于判断学号或姓名是否存在
        switch (item)
        {
        case '1':
            printf("请输入要修改的学号：");
            scanf("%s", nums);
            for (s = 0; s < r; s++)
                if (strcmp(stu[s].num, nums) == 0)
                {
                    flag = 1;
                    printf("目前该学号对应的成绩信息为:\n");
                    printheader();
                    p = stu + s;
                    printf("|%15s|%10s|%10s|%9.1f|%8.1f|%10.1f|%9.1f|%8d|\n", p->num, p->name, p->classes, p->math, p->english, p->clanguage, p->sum, p->rank);
                    printf(FORMAT1);
                    printf("\n");
                    char a;
                    printf("您是否确定要继续进行成绩修改?(y/n):\n");
                    a = _getch();
                    switch (a)
                    {
                    case 'y':
                        printf("请输入修改后的C语言成绩:");
                        scanf("%f", &stu[s].clanguage);      /*输入C语言成绩*/
                        printf("请输入修改后的高数成绩:");
                        scanf("%f", &stu[s].math);       /*输入高数课成绩*/
                        printf("请输入修改后的英语成绩:");
                        scanf("%f", &stu[s].english);      /*输入英语课成绩*/
                        stu[s].sum = stu[s].clanguage + stu[s].math + stu[s].english; /*计算出总成绩*/
                        printf("修改后的总成绩为:%f\n", stu[s].sum);
                        printf("学号%s的成绩已修改成功！您可在子菜单中继续选择!\n", stu[s].num);
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*向指定的磁盘文件写入信息*/
                        }
                        fclose(fp);
                        break;
                    case 'Y':
                        printf("请输入修改后的C语言成绩:");
                        scanf("%f", &stu[s].clanguage);      /*输入C语言成绩*/
                        printf("请输入修改后的高数成绩:");
                        scanf("%f", &stu[s].math);       /*输入高数课成绩*/
                        printf("请输入修改后的英语成绩:");
                        scanf("%f", &stu[s].english);      /*输入英语课成绩*/
                        stu[s].sum = stu[s].clanguage + stu[s].math + stu[s].english; /*计算出总成绩*/
                        printf("修改后的总成绩为:%f\n", stu[s].sum);
                        printf("学号%s的成绩已修改成功！您可在子菜单中继续选择!\n", stu[s].num);
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*向指定的磁盘文件写入信息*/
                        }
                        fclose(fp);
                        break;
                    case 'n':
                        system("cls");
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*向指定的磁盘文件写入信息*/
                        }
                        fclose(fp);
                        return;
                        break;
                    case 'N':
                        system("cls");
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*向指定的磁盘文件写入信息*/
                        }
                        fclose(fp);
                        return;
                        break;
                    }
                }
            if (0 == flag)
            {
                for (i = 0; i < m; i++)
                {
                    fwrite(&stu[i], LEN, 1, fp);  /*向指定的磁盘文件写入信息*/
                }
                fclose(fp);
                printf("学号不存在！\n\n");
                printf("您可继续从子菜单中选择：\n");
            }
            break;
        case '2':
            printf("请输入要修改的姓名：");
            scanf("%s", names);
            for (s = 0; s < r; s++)
                if (strcmp(stu[s].name, names) == 0)
                {
                    flag = 1;
                    printf("目前该姓名对应的成绩信息为:\n");
                    printheader();
                    p = stu + s;
                    printf("|%15s|%10s|%10s|%9.1f|%8.1f|%10.1f|%9.1f|%8d|\n", p->num, p->name, p->classes, p->math, p->english, p->clanguage, p->sum, p->rank);
                    printf(FORMAT1);
                    printf("\n");
                    char a;
                    printf("您是否确定要继续进行成绩修改?(y/n):\n");
                    a = _getch();
                    switch (a)
                    {
                    case 'y':
                        printf("请输入修改后的C语言成绩:");
                        scanf("%f", &stu[s].clanguage);      /*输入C语言成绩*/
                        printf("请输入修改后的高数成绩:");
                        scanf("%f", &stu[s].math);       /*输入高数课成绩*/
                        printf("请输入修改后的英语成绩:");
                        scanf("%f", &stu[s].english);      /*输入英语课成绩*/
                        stu[s].sum = stu[s].clanguage + stu[s].math + stu[s].english; /*计算出总成绩*/
                        printf("修改后的总成绩为:%f\n", stu[s].sum);
                        printf("姓名%s的成绩已修改成功！您可在子菜单中继续选择!\n", stu[s].name);
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*向指定的磁盘文件写入信息*/
                        }
                        fclose(fp);
                        break;
                    case 'Y':
                        printf("请输入修改后的C语言成绩:");
                        scanf("%f", &stu[s].clanguage);      /*输入C语言成绩*/
                        printf("请输入修改后的高数成绩:");
                        scanf("%f", &stu[s].math);       /*输入高数课成绩*/
                        printf("请输入修改后的英语成绩:");
                        scanf("%f", &stu[s].english);      /*输入英语课成绩*/
                        stu[s].sum = stu[s].clanguage + stu[s].math + stu[s].english; /*计算出总成绩*/
                        printf("修改后的总成绩为:%f\n", stu[s].sum);
                        printf("姓名%s的成绩已修改成功！您可在子菜单中继续选择!\n", stu[s].name);
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*向指定的磁盘文件写入信息*/
                        }
                        fclose(fp);
                        break;
                    case 'n':
                        system("cls");
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*向指定的磁盘文件写入信息*/
                        }
                        fclose(fp);
                        return;
                        break;
                    case 'N':
                        system("cls");
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*向指定的磁盘文件写入信息*/
                        }
                        fclose(fp);
                        return;
                        break;
                    }
                }
            if (0 == flag)
            {
                for (i = 0; i < m; i++)
                {
                    fwrite(&stu[i], LEN, 1, fp);  /*向指定的磁盘文件写入信息*/
                }
                fclose(fp);
                printf("姓名不存在！\n\n");
                printf("您可继续从子菜单中选择：\n");
            }
            break;
        case '3':
            system("cls");
            for (i = 0; i < m; i++)
            {
                fwrite(&stu[i], LEN, 1, fp);  /*向指定的磁盘文件写入信息*/
            }
            fclose(fp);
            return;
        default:
            for (i = 0; i < m; i++)
            {
                fwrite(&stu[i], LEN, 1, fp);  /*向指定的磁盘文件写入信息*/
            }
            fclose(fp);
            printf("无效选择，请在1-3中选择\n");
        }
    }
}

/**********************辅助排序函数**************************/
void rank()
{
    int i, p;
    for (i = 0; i < r; i++)
    {
        stu[i].rank = r - i;//先给所有学生赋予一个排名
    }
    int a;//用于储存结构体排名成员的数据
    struct student c;//用于储存结构体中所有成员的数据
    for (i = 0; i < r - 1; i++)
        for (p = 0; p < r - 1 - i; p++)
            if (stu[p].sum > stu[p + 1].sum)//一个冒泡排序，将学生成绩按总分进行排序
            {
                a = stu[p].rank;
                stu[p].rank = stu[p + 1].rank;
                stu[p + 1].rank = a;
                c = stu[p];//需要交换结构体在中成员的数据以继续进行冒泡排序
                stu[p] = stu[p + 1];
                stu[p + 1] = c;
            }
}

/**********************对学生成绩排序************************/
void sort()
{
    printf("\t\t\t\t----------------------------------------\n");
    printf("\t\t\t\t--------1.按排名从高到低进行排名--------\n");
    printf("\t\t\t\t--------2.按排名从低到高进行排名--------\n");
    printf("\t\t\t\t--------3.返回主菜单--------------------\n");
    printf("\t\t\t\t----------------------------------------\n");
    printf("\t\t\t\t------------请在子菜单中选择------------\n");
    file();
    rank();
    int x;
    int i;
    int y;
    struct student* p;
    while (1)
    {
        x = _getch();
        switch (x)
        {
        case '1':
            system("cls");
            system("color 3");
            printf("*********************************************************************************************************************************************************\n");
            printf("\t\t\t\t\t\t\t学生成绩管理系统\t\n");
            printf("\t\t\t\t\t\t      (按任意键返回子菜单)\t\n");
            printf("*********************************************************************************************************************************************************\n");

            printf("·\t学号\t·\t姓名\t·\t班级\t·\tC语言成绩\t·\t高数成绩\t·\t英语成绩\t·\t总成绩\t·\t排名\t·\n");
            printf("*********************************************************************************************************************************************************\n");

            for (i = r - 1; i >= 0; i--)
            {
                p = stu + i;
                printf("|%16s|%15s|%15s|%23.1f|%23.1f|%22.1f|%15.1f|%15d|\n",
                    p->num,
                    p->name,
                    p->classes,
                    p->clanguage,
                    p->math,
                    p->english,
                    p->sum,
                    p->rank);
                printf("---------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            }
            y = _getch();
            if (y)
            {
                system("cls");
                system("color 06");
                printf("\t\t\t\t------------【学生成绩排序】------------\n");
                printf("\t\t\t\t----------------------------------------\n");
                printf("\t\t\t\t--------1.按排名从高到低进行排名--------\n");
                printf("\t\t\t\t--------2.按排名从低到高进行排名--------\n");
                printf("\t\t\t\t--------3.返回主菜单--------------------\n");
                printf("\t\t\t\t----------------------------------------\n");
                printf("\t\t\t\t------------请在子菜单中选择------------\n");
            }
            break;
        case '2':
            system("cls");
            system("color E");
            printf("*********************************************************************************************************************************************************\n");
            printf("\t\t\t\t\t\t\t学生成绩管理系统\t\n");
            printf("\t\t\t\t\t\t      (按任意键返回子菜单)\t\n");
            printf("*********************************************************************************************************************************************************\n");

            printf("·\t学号\t·\t姓名\t·\t班级\t·\tC语言成绩\t·\t高数成绩\t·\t英语成绩\t·\t总成绩\t·\t排名\t·\n");
            printf("*********************************************************************************************************************************************************\n");

            for (i = 0; i < r; i++)
            {
                p = stu + i;
                printf("|%16s|%15s|%15s|%23.1f|%23.1f|%22.1f|%15.1f|%15d|\n",
                    p->num,
                    p->name,
                    p->classes,
                    p->clanguage,
                    p->math,
                    p->english,
                    p->sum,
                    p->rank);
                printf("---------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            }
            y = _getch();
            if (y);
            {
                system("cls");
                system("color 06");
                printf("\t\t\t\t------------【学生成绩排序】------------\n");
                printf("\t\t\t\t----------------------------------------\n");
                printf("\t\t\t\t--------1.按排名从高到低进行排名--------\n");
                printf("\t\t\t\t--------2.按排名从低到高进行排名--------\n");
                printf("\t\t\t\t--------3.返回主菜单--------------------\n");
                printf("\t\t\t\t----------------------------------------\n");
                printf("\t\t\t\t------------请在子菜单中选择------------\n");
            }
            break;
            break;
        case '3':
            system("cls");
            return;
        }
    }
}

/**********************统计学生成绩情况**********************/
void tongji()
{
    file();
    int i;
    float x = 0, y = 0, z = 0, t = 0;
    if (r > 0)
    {
        for (i = 0; i < r; i++)
        {
            x = x + stu[i].clanguage;
            y = y + stu[i].english;
            z = z + stu[i].math;
            t = t + stu[i].sum;
        }
        x = x / r;
        z = z / r;
        y = y / r;
        t = t / r;
        printf("\t\t\t     ------------------------------------------------------------\n");
        printf("\t\t\t\t\t               系统统计\n");
        printf("\t\t\t\t\t         (按任意键返回主菜单)\n");
        printf("\t\t\t     ------------------------------------------------------------\n");
        printf("\t\t\t     |当前系统总人数|C语言平均分|英语平均分|高数平均分|总分平均分|\n");
        printf("\t\t\t     ------------------------------------------------------------\n");
        printf("\t\t\t     |%14d|%11.1f|%10.1f|%10.1f|%10.1f|\n", r, x, y, z, t);
        printf("\t\t\t     ------------------------------------------------------------\n");
    }
    else
    {
        printf("\t\t\t     ------------------------------------------------------------\n");
        printf("\t\t\t\t\t               系统统计\n");
        printf("\t\t\t\t\t         (按任意键返回主菜单)\n");
        printf("\t\t\t     ------------------------------------------------------------\n");
        printf("\t\t\t\t\t          【当前无学生信息!】");
    }
    int c;
    c = _getch();
    if (c)
    {
        system("cls");
        return;
    }
}

/************************显示函数****************************/
void show()
{
    file();
    int i;
    struct student* p;
    system("cls");
    printf("*****************************************************************************************************************************************\n");
    printf("\t\t\t\t\t\t\t学生成绩管理系统\t\n");
    printf("\t\t\t\t\t\t      (按任意键返回主菜单)\t\n");
    printf("*****************************************************************************************************************************************\n");

    printf("·\t学号\t·\t姓名\t·\t班级\t·\tC语言成绩\t·\t高数成绩\t·\t英语成绩\t·\t总成绩\t·\n");
    printf("*****************************************************************************************************************************************\n");

    for (i = 0; i < r; i++)
    {
        p = stu + i;
        printf("|%16s|%15s|%15s|%23.1f|%23.1f|%22.1f|%15.1f|\n",
            p->num,
            p->name,
            p->classes,
            p->clanguage,
            p->math,
            p->english,
            p->sum);
        printf("-----------------------------------------------------------------------------------------------------------------------------------------\n");
    }
    system("pause");       //暂停         //清屏
    system("cls");
}

/***********************删除学生成绩信息*********************/
void del()
{
    printf("\t\t\t\t--------------------------------\n");
    printf("\t\t\t\t----------1.按学号删除----------\n");
    printf("\t\t\t\t----------2.按姓名删除----------\n");
    printf("\t\t\t\t----------3.返回主菜单----------\n");
    printf("\t\t\t\t--------------------------------\n");
    printf("\t\t\t\t--------请在子菜单中选择--------\n");
    struct student* p;
    char nums[30];
    int item;
    int flag;
    char names[20];
    int s;
    while (1)
    {
        int i, m = 0;    /*变量m表示信息或者说记录的条数*/
        FILE* fp;       /*定义文件指针fp，便于对文件进行操作*/
        if ((fp = fopen("stuData.txt", "a+")) == NULL)                             /*打开指定文件*/
        {
            printf("打开文件失败\n");
            return;
        }
        while (!feof(fp))                /*当没有运行到文件尾部时*/
        {
            if (fread(&stu[m], LEN, 1, fp) == 1)                       /*读取文件中的记录*/
            {
                m++;
                r = m;
            }
        }
        fclose(fp);
        if ((fp = fopen("stuData.txt", "wb")) == NULL)            /*打开文件用于记录信息*/
        {
            printf("打开文件失败\n");
            return;
        }
        rank();
        char item = _getch();
        flag = 0;//flag用于判断学号或姓名是否存在
        switch (item)
        {
        case '1':
            printf("请输入要删除的学号：");
            scanf("%s", nums);
            for (s = 0; s < r; s++)
                if (strcmp(stu[s].num, nums) == 0)
                {
                    flag = 1;
                    printf("目前该学号对应的成绩信息为:\n");
                    printheader();
                    p = stu + s;
                    printf("|%15s|%10s|%10s|%9.2f|%8.2f|%10.2f|%9.2f|%8d|\n", p->num, p->name, p->classes, p->math, p->english, p->clanguage, p->sum, p->rank);
                    printf(FORMAT1);
                    printf("\n");
                    char a;
                    printf("您是否确定要继续进行成绩删除?(y/n):\n");
                    a = _getch();
                    switch (a)
                    {
                    case 'y':
                        for (s; s < r - 1; s++)
                            stu[s] = stu[s + 1];
                        m = m - 1;
                        r = m;
                        printf("学生信息删除成功!您可继续从子菜单中进行选择\n\n");
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*向指定的磁盘文件写入信息*/
                        }
                        fclose(fp);
                        break;
                    case 'Y':
                        for (s; s < r - 1; s++)
                            stu[s] = stu[s + 1];
                        m = m - 1;
                        r = m;
                        printf("学生信息删除成功!您可继续从子菜单中进行选择\n\n");
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*向指定的磁盘文件写入信息*/
                        }
                        fclose(fp);
                        break;
                    case 'n':
                        printf("您可继续从子菜单中选择\n\n");
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*向指定的磁盘文件写入信息*/
                        }
                        fclose(fp);
                        break;
                    case 'N':
                        printf("您可继续从子菜单中选择\n\n");
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*向指定的磁盘文件写入信息*/
                        }
                        fclose(fp);
                        return;
                        break;
                    default:
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*向指定的磁盘文件写入信息*/
                        }
                        fclose(fp);
                        printf("选择有误,请重新在子菜单中选择!\n\n");
                    }
                }
            if (0 == flag)
            {
                for (i = 0; i < m; i++)
                {
                    fwrite(&stu[i], LEN, 1, fp);  /*向指定的磁盘文件写入信息*/
                }
                fclose(fp);
                printf("学号不存在！\n\n");
                printf("您可继续从子菜单中选择：\n\n");
            }
            break;
        case '2':
            int z;
            printf("请输入要修改的姓名：");
            scanf("%s", names);
            for (s = 0; s < r; s++)
                if (strcmp(stu[s].name, names) == 0)
                {
                    flag = 1;
                    printf("目前该姓名对应的成绩信息为:\n");
                    printheader();
                    p = stu + s;
                    printf("|%15s|%10s|%10s|%9.2f|%8.2f|%10.2f|%9.2f|%8d|\n", p->num, p->name, p->classes, p->math, p->english, p->clanguage, p->sum, p->rank);
                    printf(FORMAT1);
                    printf("\n");
                    char a;
                    printf("您是否确定要继续进行成绩删除?(y/n):\n");
                    a = _getch();
                    switch (a)
                    {
                    case 'y':
                        for (s; s < r - 1; s++)
                            stu[s] = stu[s + 1];
                        m = m - 1;
                        r = m;
                        printf("学生信息删除成功!您可继续从子菜单中进行选择:\n\n");
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*向指定的磁盘文件写入信息*/
                        }
                        fclose(fp);
                        break;
                    case 'Y':
                        for (s; s < r - 1; s++)
                            stu[s] = stu[s + 1];
                        m = m - 1;
                        r = m;
                        printf("学生信息删除成功!您可继续从子菜单中进行选择\n\n");
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*向指定的磁盘文件写入信息*/
                        }
                        fclose(fp);
                        break;
                    case 'n':
                        printf("您可继续在子菜单中选择:\n\n");
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*向指定的磁盘文件写入信息*/
                        }
                        fclose(fp);
                        return;
                        break;
                    case 'N':
                        printf("您可继续在子菜单中选择:\n\n");
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*向指定的磁盘文件写入信息*/
                        }
                        fclose(fp);
                        return;
                        break;
                    default:
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*向指定的磁盘文件写入信息*/
                        }
                        fclose(fp);
                        printf("选择有误,请重新在子菜单中选择!\n\n");
                    }
                }
            if (0 == flag)
            {
                for (i = 0; i < m; i++)
                {
                    fwrite(&stu[i], LEN, 1, fp);  /*向指定的磁盘文件写入信息*/
                }
                fclose(fp);
                printf("姓名不存在！\n\n");
                printf("您可继续从子菜单中选择：\n");
            }
            break;
        case '3':
            system("cls");
            for (i = 0; i < m; i++)
            {
                fwrite(&stu[i], LEN, 1, fp);  /*向指定的磁盘文件写入信息*/
            }
            fclose(fp);
            return;
        default:
            for (i = 0; i < m; i++)
            {
                fwrite(&stu[i], LEN, 1, fp);  /*向指定的磁盘文件写入信息*/
            }
            fclose(fp);
            printf("无效选择，请在1-3中选择\n");
        }
    }
}



int main()
{
    while (k)
    {
        menu();
    }
    return 0;
}


