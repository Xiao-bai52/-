#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
#include<string.h>
#include<Windows.h>
#define LEN sizeof(struct student)
#define FORMAT1 "----------------------------------------------------------------------------------------\n"
#define FORMAT2 "|      ѧ��     |   ����   |   �༶   |   ����  |  Ӣ��  |   C����  |   �ܷ�  |   ���� | \n"
#define FORMAT3 "|---------------|----------|----------|---------|--------|----------|---------|--------|\n"
int k = 1;      /****����ȫ�ֱ������Ʋ˵���������****/
int r = 0;      /****����ȫ�ֱ�����¼¼����Ϣ�ĸ���****/

/******************����ѧ���ɼ��ṹ��************************/
struct student
{
    char num[30];       /*ѧ��*/
    char name[15];      /*����*/
    char classes[15];   /*�༶*/
    float clanguage;    /*C���Գɼ�*/
    float math;         /*�����ɼ�*/
    float english;      /*Ӣ��ɼ�*/
    float sum;          /*�ܷ�*/
    int rank;           /*����*/
};
struct student stu[100];    /*����ȫ�ֽṹ�����飬�洢������Ϣ*/

/*********************������������*************************/
void printheader();     /*��ӡ����*/
void file();            /*���ô洢�ļ�����*/
void menu();            /*�������˵�*/
void input();           /*¼��ѧ���ɼ���Ϣ*/
void search();          /*����ѧ����Ϣ*/
void modify();          /*�޸�ѧ���ɼ���Ϣ*/
void rank();            /*����������*/
void sort();            /*����ѧ���ɼ�*/
void tongji();          /*ͳ��ѧ���ɼ�*/
void show();            /*��ʾѧ��������Ϣ*/
void del();             /*ɾ��ѧ���ɼ���Ϣ*/


/*******************���ڴ�ӡ���ĺ���***********************/
void printheader()
{
    printf(FORMAT1);
    printf(FORMAT2);
    printf(FORMAT3);
}

/*******************���ô洢�ļ��ĺ���***********************/
void file()
{
    int m = 0;
    int i = 0;
    FILE* fp;       /*�����ļ�ָ��fp�����ڶ��ļ����в���*/
    if ((fp = fopen("stuData.txt", "a+")) == NULL)                             /*��ָ���ļ�*/
    {
        printf("���ļ�ʧ��\n");
        return;
    }
    while (!feof(fp))                /*��û�����е��ļ�β��ʱ*/
    {
        if (fread(&stu[m], LEN, 1, fp) == 1)                       /*��ȡ�ļ��еļ�¼*/
        {
            m++;
            r = m;
        }
    }
    fclose(fp);
    if ((fp = fopen("stuData.txt", "wb")) == NULL)            /*���ļ����ڼ�¼��Ϣ*/
    {
        printf("���ļ�ʧ��\n");
        return;
    }
    for (i = 0; i < m; i++)
    {
        fwrite(&stu[i], LEN, 1, fp);  /*��ָ���Ĵ����ļ�д����Ϣ*/
    }
    fclose(fp);
}

/******************ѧ���ɼ�����ϵͳ�˵�**********************/
void menu()
{
    printf("\t\t\tѧ���ɼ�����ϵͳ\t\n");
    printf("     ������������������������������������������������������������\n");
    printf("\t\t|\t 0. ϵͳ����\t\t\t|\n");
    printf("\t\t|\t 1. ¼��ѧ���ɼ�\t\t|\n");
    printf("\t\t|\t 2. ����ѧ���ɼ�\t\t|\n");
    printf("\t\t|\t 3. �޸�ѧ���ɼ�\t\t|\n");
    printf("\t\t|\t 4. ѧ���ɼ�����\t\t|\n");
    printf("\t\t|\t 5. ѧ���ɼ�ͳ��\t\t|\n");
    printf("\t\t|\t 6. ��ʾѧ���ɼ�\t\t|\n");
    printf("\t\t|\t 7. ɾ��ѧ���ɼ�\t\t|\n");
    printf("\t\t|\t 8. �˳�ϵͳ\t\t\t|\n");
    printf("     ������������������������������������������������������������\n");
    printf("\t\t\t���������Ĳ���<0-8>:\n");
    system("color 6");
    char choice = _getch();
    switch (choice)
    {
    case '0':
        system("cls");
        printf("\t\t\t\t----------��ϵͳ������----------\n");
        printf("\t\t\t\t1. ��ϵͳ���¼��100��ѧ���ĳɼ�\n");
        printf("\t\t\t\t2. ��ϵͳ��ɾ�����޸�ѧ���ĳɼ�\n");
        printf("\t\t\t\t3. �밴��ϵͳ����ʾ���в���\n");
        printf("\t\t\t\t4. ��лʹ��\n");
        printf("\t\t\t\t--------------------------------\n");
        printf("\t\t\t\t------(��������������˵�)------\n");
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
        printf("----------��¼��ѧ���ɼ���----------\n");
        input();
        break;
    case '2':
        system("cls");
        printf("\t\t\t\t------������ѧ���ɼ���------\n");
        search();
        break;
    case '3':
        system("cls");
        printf("\t\t\t    ----------���޸�ѧ���ɼ���----------\n");
        modify();
        break;
    case '4':
        system("cls");
        printf("\t\t\t\t------------��ѧ���ɼ�����------------\n");
        sort();
        break;
    case '5':
        system("cls");
        printf("\t\t\t     ----------------------��ѧ���ɼ�ͳ�ơ�----------------------\n");
        tongji();
        break;
    case '6':
        system("cls");
        printf("----------����ʾѧ���ɼ���----------\n");
        show();
        break;
    case '7':
        system("cls");
        printf("\t\t\t        --------��ɾ��ѧ���ɼ���--------\n");
        del();
        break;
    case '8':
        k = 0;
        system("cls");
        printf("��������������˳�,��л����ʹ�ã�\n");
        system("pause");
        exit(0);
        break;
    default:
        printf("ѡ�����,����������");
        system("cls");
        break;
    }
}


/**********************¼��ѧ���ɼ���Ϣ**********************/
void input()
{
    int i, m = 0;    /*����m��ʾ��Ϣ����˵��¼������*/
    char ch[2];
    FILE* fp;       /*�����ļ�ָ��fp�����ڶ��ļ����в���*/
    if ((fp = fopen("stuData.txt", "a+")) == NULL)                             /*��ָ���ļ�*/
    {
        printf("���ļ�ʧ��\n");
        return;
    }
    while (!feof(fp))                /*��û�����е��ļ�β��ʱ*/
    {
        if (fread(&stu[m], LEN, 1, fp) == 1)                       /*��ȡ�ļ��еļ�¼*/
        {
            m++;
            r = m;
        }
    }
    fclose(fp);                     /*�ر��ļ�ָ��fp��ָ����ļ�*/
    if (m == 0)
        printf("��ʱû��ѧ������!\n");
    else
    {
        printf("����%dλѧ����Ϣ\n", m);
    }
    if ((fp = fopen("stuData.txt", "wb")) == NULL)            /*���ļ����ڼ�¼��Ϣ*/
    {
        printf("���ļ�ʧ��\n");
        return;
    }
    for (i = 0; i < m; i++)
    {
        fwrite(&stu[i], LEN, 1, fp);  /*��ָ���Ĵ����ļ�д����Ϣ*/
    }
    printf("�Ƿ�Ҫ¼��ѧ���ɼ�(y/n):");
    scanf("%s", ch);
    while (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)                /*�ж��Ƿ�Ҫ¼������Ϣ*/
    {
        printf("������ѧ��:");
        scanf("%s", stu[m].num);   /*����ѧ��ѧ��*/
        for (i = 0; i < m; i++)
            if (strcmp(stu[m].num, stu[i].num) == 0) /*�ӵ�һ����¼��ʼ�жϣ��Ƿ�͵�m����¼��ѧ��һ��*/
            {
                printf("��ѧ���Ѵ��ڣ�����������������˵���");
                _getch();
                system("cls");
                fclose(fp);
                return;
            }
        /*���ѧ�ſ��ã������������������*/
        printf("����������(ͬ��ѧ�������֣�:");
        scanf("%s", stu[m].name);/*����ѧ������*/
        printf("������༶:");
        scanf("%s", stu[m].classes);    /*����༶*/
        printf("������C���Գɼ�:");
        scanf("%f", &stu[m].clanguage);      /*����C���Գɼ�*/
        printf("����������ɼ�:");
        scanf("%f", &stu[m].math);       /*��������γɼ�*/
        printf("������Ӣ��ɼ�:");
        scanf("%f", &stu[m].english);      /*����Ӣ��γɼ�*/
        stu[m].sum = stu[m].clanguage + stu[m].math + stu[m].english; /*������ܳɼ�*/
        printf("�ܳɼ�:%.1f\n", stu[m].sum);
        if (fwrite(&stu[m], LEN, 1, fp) != 1) /*����¼�����Ϣд��ָ���Ĵ����ļ�*/
        {
            printf("����ʧ��!");
            _getch();
        }
        else
        {
            printf("%s �ĳɼ��ѱ���!\n", stu[m].name);
            m++;
            r = m;
        }
        printf("�Ƿ����¼��ɼ�?(y/n):");   /*ѯ���Ƿ����*/
        scanf("%s", ch);
        printf("\n");
    }
    fclose(fp);
    printf("�����ɹ�!\n");
    system("cls");
}

/**********************����ѧ���ɼ���Ϣ**********************/
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
    printf("\t\t\t\t--------1.��ѧ�Ų�ѯ--------\n");
    printf("\t\t\t\t--------2.��������ѯ--------\n");
    printf("\t\t\t\t--------3.�������˵�--------\n");
    printf("\t\t\t\t----------------------------\n");
    printf("\t\t\t\t------�����Ӳ˵���ѡ��------\n");
    rank();
    while (1)
    {
        char item = _getch();
        flag = 0;//flag�����ж�ѧ�Ż������Ƿ����
        switch (item)
        {
        case '1':
            printf("������Ҫ��ѯ��ѧ�ţ�");
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
                    printf("���ɼ������Ӳ˵���ѡ��\n");
                }
            if (0 == flag)
            {
                printf("ѧ�Ų����ڣ�\n\n");
                printf("���ɼ������Ӳ˵���ѡ��\n");
            }
            break;
        case '2':
            printf("������Ҫ��ѯ������:");
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
                    printf("���ɼ������Ӳ˵���ѡ��\n");
                }
            if (0 == flag)
            {
                printf("������������\n\n");
                printf("���ɼ������Ӳ˵���ѡ��\n");
            }
            break;
        case '3':
            system("cls");
            return;
        default:
            printf("��Чѡ������1-3��ѡ��\n");
        }
    }
}

/**********************�޸�ѧ���ɼ���Ϣ**********************/
void modify()
{

    struct student* p;
    char nums[30];
    int item;//���ڿ��ƶ����˵���ѡ��
    int flag;
    char names[20];
    int s;
    printf("\t\t\t    ------------------------------------\n");
    printf("\t\t\t    ------------1.��ѧ���޸�------------\n");
    printf("\t\t\t    ------------2.�������޸�------------\n");
    printf("\t\t\t    ------------3.�������˵�------------\n");
    printf("\t\t\t    ------------------------------------\n");
    printf("\t\t\t    ----------�����Ӳ˵���ѡ��----------\n");
    while (1)
    {
        int i, m = 0;    /*����m��ʾ��Ϣ����˵��¼������*/
        FILE* fp;       /*�����ļ�ָ��fp�����ڶ��ļ����в���*/
        if ((fp = fopen("stuData.txt", "a+")) == NULL)                             /*��ָ���ļ�*/
        {
            printf("���ļ�ʧ��\n");
            return;
        }
        while (!feof(fp))                /*��û�����е��ļ�β��ʱ*/
        {
            if (fread(&stu[m], LEN, 1, fp) == 1)                       /*��ȡ�ļ��еļ�¼*/
            {
                m++;
                r = m;
            }
        }
        fclose(fp);
        if ((fp = fopen("stuData.txt", "wb")) == NULL)            /*���ļ����ڼ�¼��Ϣ*/
        {
            printf("���ļ�ʧ��\n");
            return;
        }
        rank();
        char item = _getch();
        flag = 0;//flag�����ж�ѧ�Ż������Ƿ����
        switch (item)
        {
        case '1':
            printf("������Ҫ�޸ĵ�ѧ�ţ�");
            scanf("%s", nums);
            for (s = 0; s < r; s++)
                if (strcmp(stu[s].num, nums) == 0)
                {
                    flag = 1;
                    printf("Ŀǰ��ѧ�Ŷ�Ӧ�ĳɼ���ϢΪ:\n");
                    printheader();
                    p = stu + s;
                    printf("|%15s|%10s|%10s|%9.1f|%8.1f|%10.1f|%9.1f|%8d|\n", p->num, p->name, p->classes, p->math, p->english, p->clanguage, p->sum, p->rank);
                    printf(FORMAT1);
                    printf("\n");
                    char a;
                    printf("���Ƿ�ȷ��Ҫ�������гɼ��޸�?(y/n):\n");
                    a = _getch();
                    switch (a)
                    {
                    case 'y':
                        printf("�������޸ĺ��C���Գɼ�:");
                        scanf("%f", &stu[s].clanguage);      /*����C���Գɼ�*/
                        printf("�������޸ĺ�ĸ����ɼ�:");
                        scanf("%f", &stu[s].math);       /*��������γɼ�*/
                        printf("�������޸ĺ��Ӣ��ɼ�:");
                        scanf("%f", &stu[s].english);      /*����Ӣ��γɼ�*/
                        stu[s].sum = stu[s].clanguage + stu[s].math + stu[s].english; /*������ܳɼ�*/
                        printf("�޸ĺ���ܳɼ�Ϊ:%f\n", stu[s].sum);
                        printf("ѧ��%s�ĳɼ����޸ĳɹ����������Ӳ˵��м���ѡ��!\n", stu[s].num);
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*��ָ���Ĵ����ļ�д����Ϣ*/
                        }
                        fclose(fp);
                        break;
                    case 'Y':
                        printf("�������޸ĺ��C���Գɼ�:");
                        scanf("%f", &stu[s].clanguage);      /*����C���Գɼ�*/
                        printf("�������޸ĺ�ĸ����ɼ�:");
                        scanf("%f", &stu[s].math);       /*��������γɼ�*/
                        printf("�������޸ĺ��Ӣ��ɼ�:");
                        scanf("%f", &stu[s].english);      /*����Ӣ��γɼ�*/
                        stu[s].sum = stu[s].clanguage + stu[s].math + stu[s].english; /*������ܳɼ�*/
                        printf("�޸ĺ���ܳɼ�Ϊ:%f\n", stu[s].sum);
                        printf("ѧ��%s�ĳɼ����޸ĳɹ����������Ӳ˵��м���ѡ��!\n", stu[s].num);
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*��ָ���Ĵ����ļ�д����Ϣ*/
                        }
                        fclose(fp);
                        break;
                    case 'n':
                        system("cls");
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*��ָ���Ĵ����ļ�д����Ϣ*/
                        }
                        fclose(fp);
                        return;
                        break;
                    case 'N':
                        system("cls");
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*��ָ���Ĵ����ļ�д����Ϣ*/
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
                    fwrite(&stu[i], LEN, 1, fp);  /*��ָ���Ĵ����ļ�д����Ϣ*/
                }
                fclose(fp);
                printf("ѧ�Ų����ڣ�\n\n");
                printf("���ɼ������Ӳ˵���ѡ��\n");
            }
            break;
        case '2':
            printf("������Ҫ�޸ĵ�������");
            scanf("%s", names);
            for (s = 0; s < r; s++)
                if (strcmp(stu[s].name, names) == 0)
                {
                    flag = 1;
                    printf("Ŀǰ��������Ӧ�ĳɼ���ϢΪ:\n");
                    printheader();
                    p = stu + s;
                    printf("|%15s|%10s|%10s|%9.1f|%8.1f|%10.1f|%9.1f|%8d|\n", p->num, p->name, p->classes, p->math, p->english, p->clanguage, p->sum, p->rank);
                    printf(FORMAT1);
                    printf("\n");
                    char a;
                    printf("���Ƿ�ȷ��Ҫ�������гɼ��޸�?(y/n):\n");
                    a = _getch();
                    switch (a)
                    {
                    case 'y':
                        printf("�������޸ĺ��C���Գɼ�:");
                        scanf("%f", &stu[s].clanguage);      /*����C���Գɼ�*/
                        printf("�������޸ĺ�ĸ����ɼ�:");
                        scanf("%f", &stu[s].math);       /*��������γɼ�*/
                        printf("�������޸ĺ��Ӣ��ɼ�:");
                        scanf("%f", &stu[s].english);      /*����Ӣ��γɼ�*/
                        stu[s].sum = stu[s].clanguage + stu[s].math + stu[s].english; /*������ܳɼ�*/
                        printf("�޸ĺ���ܳɼ�Ϊ:%f\n", stu[s].sum);
                        printf("����%s�ĳɼ����޸ĳɹ����������Ӳ˵��м���ѡ��!\n", stu[s].name);
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*��ָ���Ĵ����ļ�д����Ϣ*/
                        }
                        fclose(fp);
                        break;
                    case 'Y':
                        printf("�������޸ĺ��C���Գɼ�:");
                        scanf("%f", &stu[s].clanguage);      /*����C���Գɼ�*/
                        printf("�������޸ĺ�ĸ����ɼ�:");
                        scanf("%f", &stu[s].math);       /*��������γɼ�*/
                        printf("�������޸ĺ��Ӣ��ɼ�:");
                        scanf("%f", &stu[s].english);      /*����Ӣ��γɼ�*/
                        stu[s].sum = stu[s].clanguage + stu[s].math + stu[s].english; /*������ܳɼ�*/
                        printf("�޸ĺ���ܳɼ�Ϊ:%f\n", stu[s].sum);
                        printf("����%s�ĳɼ����޸ĳɹ����������Ӳ˵��м���ѡ��!\n", stu[s].name);
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*��ָ���Ĵ����ļ�д����Ϣ*/
                        }
                        fclose(fp);
                        break;
                    case 'n':
                        system("cls");
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*��ָ���Ĵ����ļ�д����Ϣ*/
                        }
                        fclose(fp);
                        return;
                        break;
                    case 'N':
                        system("cls");
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*��ָ���Ĵ����ļ�д����Ϣ*/
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
                    fwrite(&stu[i], LEN, 1, fp);  /*��ָ���Ĵ����ļ�д����Ϣ*/
                }
                fclose(fp);
                printf("���������ڣ�\n\n");
                printf("���ɼ������Ӳ˵���ѡ��\n");
            }
            break;
        case '3':
            system("cls");
            for (i = 0; i < m; i++)
            {
                fwrite(&stu[i], LEN, 1, fp);  /*��ָ���Ĵ����ļ�д����Ϣ*/
            }
            fclose(fp);
            return;
        default:
            for (i = 0; i < m; i++)
            {
                fwrite(&stu[i], LEN, 1, fp);  /*��ָ���Ĵ����ļ�д����Ϣ*/
            }
            fclose(fp);
            printf("��Чѡ������1-3��ѡ��\n");
        }
    }
}

/**********************����������**************************/
void rank()
{
    int i, p;
    for (i = 0; i < r; i++)
    {
        stu[i].rank = r - i;//�ȸ�����ѧ������һ������
    }
    int a;//���ڴ���ṹ��������Ա������
    struct student c;//���ڴ���ṹ�������г�Ա������
    for (i = 0; i < r - 1; i++)
        for (p = 0; p < r - 1 - i; p++)
            if (stu[p].sum > stu[p + 1].sum)//һ��ð�����򣬽�ѧ���ɼ����ֽܷ�������
            {
                a = stu[p].rank;
                stu[p].rank = stu[p + 1].rank;
                stu[p + 1].rank = a;
                c = stu[p];//��Ҫ�����ṹ�����г�Ա�������Լ�������ð������
                stu[p] = stu[p + 1];
                stu[p + 1] = c;
            }
}

/**********************��ѧ���ɼ�����************************/
void sort()
{
    printf("\t\t\t\t----------------------------------------\n");
    printf("\t\t\t\t--------1.�������Ӹߵ��ͽ�������--------\n");
    printf("\t\t\t\t--------2.�������ӵ͵��߽�������--------\n");
    printf("\t\t\t\t--------3.�������˵�--------------------\n");
    printf("\t\t\t\t----------------------------------------\n");
    printf("\t\t\t\t------------�����Ӳ˵���ѡ��------------\n");
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
            printf("\t\t\t\t\t\t\tѧ���ɼ�����ϵͳ\t\n");
            printf("\t\t\t\t\t\t      (������������Ӳ˵�)\t\n");
            printf("*********************************************************************************************************************************************************\n");

            printf("��\tѧ��\t��\t����\t��\t�༶\t��\tC���Գɼ�\t��\t�����ɼ�\t��\tӢ��ɼ�\t��\t�ܳɼ�\t��\t����\t��\n");
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
                printf("\t\t\t\t------------��ѧ���ɼ�����------------\n");
                printf("\t\t\t\t----------------------------------------\n");
                printf("\t\t\t\t--------1.�������Ӹߵ��ͽ�������--------\n");
                printf("\t\t\t\t--------2.�������ӵ͵��߽�������--------\n");
                printf("\t\t\t\t--------3.�������˵�--------------------\n");
                printf("\t\t\t\t----------------------------------------\n");
                printf("\t\t\t\t------------�����Ӳ˵���ѡ��------------\n");
            }
            break;
        case '2':
            system("cls");
            system("color E");
            printf("*********************************************************************************************************************************************************\n");
            printf("\t\t\t\t\t\t\tѧ���ɼ�����ϵͳ\t\n");
            printf("\t\t\t\t\t\t      (������������Ӳ˵�)\t\n");
            printf("*********************************************************************************************************************************************************\n");

            printf("��\tѧ��\t��\t����\t��\t�༶\t��\tC���Գɼ�\t��\t�����ɼ�\t��\tӢ��ɼ�\t��\t�ܳɼ�\t��\t����\t��\n");
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
                printf("\t\t\t\t------------��ѧ���ɼ�����------------\n");
                printf("\t\t\t\t----------------------------------------\n");
                printf("\t\t\t\t--------1.�������Ӹߵ��ͽ�������--------\n");
                printf("\t\t\t\t--------2.�������ӵ͵��߽�������--------\n");
                printf("\t\t\t\t--------3.�������˵�--------------------\n");
                printf("\t\t\t\t----------------------------------------\n");
                printf("\t\t\t\t------------�����Ӳ˵���ѡ��------------\n");
            }
            break;
            break;
        case '3':
            system("cls");
            return;
        }
    }
}

/**********************ͳ��ѧ���ɼ����**********************/
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
        printf("\t\t\t\t\t               ϵͳͳ��\n");
        printf("\t\t\t\t\t         (��������������˵�)\n");
        printf("\t\t\t     ------------------------------------------------------------\n");
        printf("\t\t\t     |��ǰϵͳ������|C����ƽ����|Ӣ��ƽ����|����ƽ����|�ܷ�ƽ����|\n");
        printf("\t\t\t     ------------------------------------------------------------\n");
        printf("\t\t\t     |%14d|%11.1f|%10.1f|%10.1f|%10.1f|\n", r, x, y, z, t);
        printf("\t\t\t     ------------------------------------------------------------\n");
    }
    else
    {
        printf("\t\t\t     ------------------------------------------------------------\n");
        printf("\t\t\t\t\t               ϵͳͳ��\n");
        printf("\t\t\t\t\t         (��������������˵�)\n");
        printf("\t\t\t     ------------------------------------------------------------\n");
        printf("\t\t\t\t\t          ����ǰ��ѧ����Ϣ!��");
    }
    int c;
    c = _getch();
    if (c)
    {
        system("cls");
        return;
    }
}

/************************��ʾ����****************************/
void show()
{
    file();
    int i;
    struct student* p;
    system("cls");
    printf("*****************************************************************************************************************************************\n");
    printf("\t\t\t\t\t\t\tѧ���ɼ�����ϵͳ\t\n");
    printf("\t\t\t\t\t\t      (��������������˵�)\t\n");
    printf("*****************************************************************************************************************************************\n");

    printf("��\tѧ��\t��\t����\t��\t�༶\t��\tC���Գɼ�\t��\t�����ɼ�\t��\tӢ��ɼ�\t��\t�ܳɼ�\t��\n");
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
    system("pause");       //��ͣ         //����
    system("cls");
}

/***********************ɾ��ѧ���ɼ���Ϣ*********************/
void del()
{
    printf("\t\t\t\t--------------------------------\n");
    printf("\t\t\t\t----------1.��ѧ��ɾ��----------\n");
    printf("\t\t\t\t----------2.������ɾ��----------\n");
    printf("\t\t\t\t----------3.�������˵�----------\n");
    printf("\t\t\t\t--------------------------------\n");
    printf("\t\t\t\t--------�����Ӳ˵���ѡ��--------\n");
    struct student* p;
    char nums[30];
    int item;
    int flag;
    char names[20];
    int s;
    while (1)
    {
        int i, m = 0;    /*����m��ʾ��Ϣ����˵��¼������*/
        FILE* fp;       /*�����ļ�ָ��fp�����ڶ��ļ����в���*/
        if ((fp = fopen("stuData.txt", "a+")) == NULL)                             /*��ָ���ļ�*/
        {
            printf("���ļ�ʧ��\n");
            return;
        }
        while (!feof(fp))                /*��û�����е��ļ�β��ʱ*/
        {
            if (fread(&stu[m], LEN, 1, fp) == 1)                       /*��ȡ�ļ��еļ�¼*/
            {
                m++;
                r = m;
            }
        }
        fclose(fp);
        if ((fp = fopen("stuData.txt", "wb")) == NULL)            /*���ļ����ڼ�¼��Ϣ*/
        {
            printf("���ļ�ʧ��\n");
            return;
        }
        rank();
        char item = _getch();
        flag = 0;//flag�����ж�ѧ�Ż������Ƿ����
        switch (item)
        {
        case '1':
            printf("������Ҫɾ����ѧ�ţ�");
            scanf("%s", nums);
            for (s = 0; s < r; s++)
                if (strcmp(stu[s].num, nums) == 0)
                {
                    flag = 1;
                    printf("Ŀǰ��ѧ�Ŷ�Ӧ�ĳɼ���ϢΪ:\n");
                    printheader();
                    p = stu + s;
                    printf("|%15s|%10s|%10s|%9.2f|%8.2f|%10.2f|%9.2f|%8d|\n", p->num, p->name, p->classes, p->math, p->english, p->clanguage, p->sum, p->rank);
                    printf(FORMAT1);
                    printf("\n");
                    char a;
                    printf("���Ƿ�ȷ��Ҫ�������гɼ�ɾ��?(y/n):\n");
                    a = _getch();
                    switch (a)
                    {
                    case 'y':
                        for (s; s < r - 1; s++)
                            stu[s] = stu[s + 1];
                        m = m - 1;
                        r = m;
                        printf("ѧ����Ϣɾ���ɹ�!���ɼ������Ӳ˵��н���ѡ��\n\n");
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*��ָ���Ĵ����ļ�д����Ϣ*/
                        }
                        fclose(fp);
                        break;
                    case 'Y':
                        for (s; s < r - 1; s++)
                            stu[s] = stu[s + 1];
                        m = m - 1;
                        r = m;
                        printf("ѧ����Ϣɾ���ɹ�!���ɼ������Ӳ˵��н���ѡ��\n\n");
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*��ָ���Ĵ����ļ�д����Ϣ*/
                        }
                        fclose(fp);
                        break;
                    case 'n':
                        printf("���ɼ������Ӳ˵���ѡ��\n\n");
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*��ָ���Ĵ����ļ�д����Ϣ*/
                        }
                        fclose(fp);
                        break;
                    case 'N':
                        printf("���ɼ������Ӳ˵���ѡ��\n\n");
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*��ָ���Ĵ����ļ�д����Ϣ*/
                        }
                        fclose(fp);
                        return;
                        break;
                    default:
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*��ָ���Ĵ����ļ�д����Ϣ*/
                        }
                        fclose(fp);
                        printf("ѡ������,���������Ӳ˵���ѡ��!\n\n");
                    }
                }
            if (0 == flag)
            {
                for (i = 0; i < m; i++)
                {
                    fwrite(&stu[i], LEN, 1, fp);  /*��ָ���Ĵ����ļ�д����Ϣ*/
                }
                fclose(fp);
                printf("ѧ�Ų����ڣ�\n\n");
                printf("���ɼ������Ӳ˵���ѡ��\n\n");
            }
            break;
        case '2':
            int z;
            printf("������Ҫ�޸ĵ�������");
            scanf("%s", names);
            for (s = 0; s < r; s++)
                if (strcmp(stu[s].name, names) == 0)
                {
                    flag = 1;
                    printf("Ŀǰ��������Ӧ�ĳɼ���ϢΪ:\n");
                    printheader();
                    p = stu + s;
                    printf("|%15s|%10s|%10s|%9.2f|%8.2f|%10.2f|%9.2f|%8d|\n", p->num, p->name, p->classes, p->math, p->english, p->clanguage, p->sum, p->rank);
                    printf(FORMAT1);
                    printf("\n");
                    char a;
                    printf("���Ƿ�ȷ��Ҫ�������гɼ�ɾ��?(y/n):\n");
                    a = _getch();
                    switch (a)
                    {
                    case 'y':
                        for (s; s < r - 1; s++)
                            stu[s] = stu[s + 1];
                        m = m - 1;
                        r = m;
                        printf("ѧ����Ϣɾ���ɹ�!���ɼ������Ӳ˵��н���ѡ��:\n\n");
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*��ָ���Ĵ����ļ�д����Ϣ*/
                        }
                        fclose(fp);
                        break;
                    case 'Y':
                        for (s; s < r - 1; s++)
                            stu[s] = stu[s + 1];
                        m = m - 1;
                        r = m;
                        printf("ѧ����Ϣɾ���ɹ�!���ɼ������Ӳ˵��н���ѡ��\n\n");
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*��ָ���Ĵ����ļ�д����Ϣ*/
                        }
                        fclose(fp);
                        break;
                    case 'n':
                        printf("���ɼ������Ӳ˵���ѡ��:\n\n");
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*��ָ���Ĵ����ļ�д����Ϣ*/
                        }
                        fclose(fp);
                        return;
                        break;
                    case 'N':
                        printf("���ɼ������Ӳ˵���ѡ��:\n\n");
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*��ָ���Ĵ����ļ�д����Ϣ*/
                        }
                        fclose(fp);
                        return;
                        break;
                    default:
                        for (i = 0; i < m; i++)
                        {
                            fwrite(&stu[i], LEN, 1, fp);  /*��ָ���Ĵ����ļ�д����Ϣ*/
                        }
                        fclose(fp);
                        printf("ѡ������,���������Ӳ˵���ѡ��!\n\n");
                    }
                }
            if (0 == flag)
            {
                for (i = 0; i < m; i++)
                {
                    fwrite(&stu[i], LEN, 1, fp);  /*��ָ���Ĵ����ļ�д����Ϣ*/
                }
                fclose(fp);
                printf("���������ڣ�\n\n");
                printf("���ɼ������Ӳ˵���ѡ��\n");
            }
            break;
        case '3':
            system("cls");
            for (i = 0; i < m; i++)
            {
                fwrite(&stu[i], LEN, 1, fp);  /*��ָ���Ĵ����ļ�д����Ϣ*/
            }
            fclose(fp);
            return;
        default:
            for (i = 0; i < m; i++)
            {
                fwrite(&stu[i], LEN, 1, fp);  /*��ָ���Ĵ����ļ�д����Ϣ*/
            }
            fclose(fp);
            printf("��Чѡ������1-3��ѡ��\n");
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


