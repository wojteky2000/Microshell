#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <signal.h>
#include <wait.h>
#include <errno.h>
#include <ctype.h>
#include <termios.h>

int s0;
int s1;
int s2;
int ifw;
pid_t prnt;
pid_t pid;
int ife;
int ifcdp;
struct termios o;

void obs_sig(int s)
{
    printf("\b \b\b \b");
    if((prnt!=getpid())||(pid==-1))
    {
        tcsetattr(0,0,&o);
        printf("\n");
        exit(0);
    }
    else
    {
        ife=0;
    }
}
void whatis(char *p, int *t)
{
    struct stat ps;
    lstat(p,&ps);
    t[0]=S_ISREG(ps.st_mode);
    t[1]=S_ISDIR(ps.st_mode);
    t[2]=S_ISLNK(ps.st_mode);
    t[3]=S_ISCHR(ps.st_mode);
    t[4]=S_ISBLK(ps.st_mode);
    t[5]=S_ISFIFO(ps.st_mode);
}
void _mkdir(char *p);
void copy_file(char *file1, char *file2);
void cpr(char *fr, char *f1, char *f2, char *f3);
void aq1(char *t1, char *t2, int *j, int ifc, int *c);
void dupp(char *t, int *j);
void tree(char *fr, int g, int *t, int *valdir, int *valfile, int *ifr);
void obs_del(char *nap, int *innap, int *h)
{
    if(*innap<*h)
    {
        int hm=0;
        while(*innap<*h)
        {
            hm++;
            nap[*innap]=nap[*innap+1];
            printf("%c",nap[*innap]);
            *innap+=1;
        }
        printf("\033[C\b \b");
        int i=0;
        *h-=1;
        while(i<hm-1)
        {
            *innap-=1;
            printf("\b");
            i++;
        }
        *innap-=1;
    }
}
void obs_bcksp(char *nap, int *innap, int *h)
{
    *innap-=1;
    printf("\b");
    int hm=0;
    while(*innap<*h)
    {
        hm++;
        nap[*innap]=nap[*innap+1];
        printf("%c",nap[*innap]);
        *innap+=1;
    }
    *h-=1;
    printf("\033[C\b \b");
    int i=1;
    while(i<hm)
    {
        printf("\b");
        i++;
        *innap-=1;
    }
    *innap-=1;
}
void obs_ins(char *nap, int *innap, int *h, char c);
int main()
{
    prnt=getpid();
    char buf1[10000];
    char buf2[10000];
    char com[10000];
    char comf[10000];
    char arg[100][10000];
    char t1[100000];
    char t2[100000];
    int tt[10000];
    memset(t1,0,100000*sizeof(t1[0]));
    memset(t2,0,100000*sizeof(t2[0]));
    FILE *his;
    FILE *hiss;
    char hisp[10000];
    getcwd(hisp,10000);
    strcat(hisp,"/his.txt");
    int flaghis=1;
    int flagpath=1;
    int valpipe;
    int inhis;
    int in;
    int flag;
    int flagcpr;
    int incpr;
    int flagins=0;
    int ifr;
    s0=dup(0);
    s1=dup(1);
    s2=dup(2);
    int ifa;
    int ifq;
    int i;
    int j;
    int ifd;
    int h1;
    int h2;
    char *h3;
    int incomf;
    int hmtd;
    signal(SIGINT,obs_sig);
    signal(SIGQUIT,obs_sig);
    struct termios n;
    tcgetattr(0,&o);
    n=o;
    n.c_lflag&=~(ICANON|ECHO);
    while(1)
    {
        wait(NULL);
        pid=-1;
        inhis=2147483647;
        h1=0;
        h2=0;
        memset(buf1,0,10000*sizeof(buf1[0]));
        memset(buf2,0,10000*sizeof(buf2[0]));
        memset(com,0,10000*sizeof(com[0]));
        memset(comf,0,10000*sizeof(com[0]));
        memset(tt,1,10000*sizeof(tt[0]));
        ifd=0;
        flagcpr=0;
        i=0;
        j=0;
        ifw=1;
        ifcdp=0;
        while(j<100)
        {
            memset(arg[j],0,10000*sizeof(arg[j][0]));
            j++;
        }
        j=0;
        dup2(s0,0);
        dup2(s1,1);
        dup2(s2,2);
        ifr=1;
        flagpath=1;
        flagcpr=0;
        valpipe=0;
        printf("\033[1;32m%s:\033[1;34m[%s] \033[0m$ ",getenv("USER"),getcwd(buf1,10000));
        char c='\0';
        incomf=0;
        hmtd=0;
        tcsetattr(0,0,&n);
        h1=0;
        while((c=getchar())!='\n')
        {
            if(c=='\033')
            {
                c=getchar();
                c=getchar();
                if(c=='A')
                {
                    hiss=fopen(hisp,"r");
                    if((hiss!=NULL)&&(inhis!=1))
                    {
                        memset(buf1,0,10000*sizeof(buf1[0]));
                        memset(buf2,0,10000*sizeof(buf2[0]));
                        h3=fgets(buf1,10000,hiss);
                        i=1;
                        while((h3!=NULL)&&(i<inhis))
                        {
                            strcpy(buf2,buf1);
                            h3=fgets(buf1,10000,hiss);
                            i++;
                        }
                        if(inhis==2147483647)
                        {
                            inhis=i-1;
                        }
                        else
                        {
                            inhis--;
                        }
                        i=0;
                        if(flaghis)
                        {
                            flaghis=0;
                            while(i<incomf)
                            {
                                printf("\b \b");
                                i++;
                            }
                        }
                        else
                        {
                            while(i<hmtd)
                            {
                                printf("\b \b");
                                i++;
                            }
                        }
                        hmtd=strlen(buf2);
                        if(buf2[hmtd-1]=='\n')
                        {
                            buf2[hmtd-1]='\0';
                            hmtd--;
                        }
                        h2=hmtd;
                        printf("%s",buf2);
                        fclose(hiss);
                    }
                }
                else if((c=='B')&&!flaghis)
                {
                    hiss=fopen(hisp,"r");
                    if(hiss!=NULL)
                    {
                        memset(buf2,0,10000*sizeof(buf1[0]));
                        i=1;
                        h3=fgets(buf2,10000,hiss);
                        while((h3!=NULL)&&(i<=inhis))
                        {
                            h3=fgets(buf2,10000,hiss);
                            i++;
                        }
                        inhis++;
                        i=0;
                        while(i<hmtd)
                        {
                            printf("\b \b");
                            i++;
                        }
                        if(h3==NULL)
                        {
                            flaghis=1;
                            hmtd=0;
                            h2=0;
                            printf("%s",comf);
                        }
                        else
                        {
                            hmtd=strlen(buf2);
                            if(buf2[hmtd-1]=='\n')
                            {
                                buf2[hmtd-1]='\0';
                                hmtd--;
                            }
                            h2=hmtd;
                            printf("%s",buf2);
                        }
                    }
                }
                else if(c=='C')
                {
                    if((incomf<h1)&&(flaghis))
                    {
                        incomf++;
                        printf("\033[C");
                    }
                    else if((hmtd<h2)&&(!flaghis))
                    {
                        hmtd++;
                        printf("\033[C");
                    }
                }
                else if(c=='D')
                {
                    if((incomf>0)&&(flaghis))
                    {
                        incomf--;
                        printf("\b");
                    }
                    else if((hmtd>0)&&(!flaghis))
                    {
                        hmtd--;
                        printf("\b");
                    }
                }
                else if(c=='3')
                {
                    c=getchar();
                    printf("\033[C");
                    printf("\b \b");
                    if(flaghis)
                    {
                        if(incomf<h1)
                        {
                            obs_del(comf,&incomf,&h1);
                        }
                    }
                    else
                    {
                        if(hmtd<h2)
                        {
                            obs_del(buf2,&hmtd,&h2);
                        }
                    }
                }
                else if(c=='2')
                {
                    c=getchar();
                    if(c=='~')
                    {
                        if(flagins)
                        {
                            flagins=0;
                        }
                        else
                        {
                            flagins=1;
                        }
                    }
                }
            }
            else if(c=='\177')
            {
                if((flaghis)&&(incomf>0))
                {
                    obs_bcksp(comf,&incomf,&h1);
                }
                else if((!flaghis)&&(hmtd>0))
                {
                    obs_bcksp(buf2,&hmtd,&h2);
                }
            }
            else
            {
                if(c!='\t')
                {
                    printf("%c",c);
                }
                else
                {
                    printf("    ");
                }
                if(flaghis)
                {
                    if(flagins)
                    {
                        if(c!='\t')
                        {
                            comf[incomf]=c;
                            incomf++;
                            if(incomf>h1)
                            {
                                h1=incomf;
                            }
                        }
                        else
                        {
                            int ile=0;
                            if(comf[incomf]=='\0')
                            {
                                ile++;
                            }
                            comf[incomf]=' ';
                            if(comf[incomf+1]=='\0')
                            {
                                ile++;
                            }
                            comf[incomf+1]=' ';
                            if(comf[incomf+2]=='\0')
                            {
                                ile++;
                            }
                            comf[incomf+2]=' ';
                            if(comf[incomf+3]=='\0')
                            {
                                ile++;
                            }
                            comf[incomf+3]=' ';
                            incomf+=4;
                            if(incomf>h1)
                            {
                                h1=incomf;
                            }
                        }
                    }
                    else
                    {
                        obs_ins(comf,&incomf,&h1,c);
                    }
                }
                else
                {
                    if(flagins)
                    {
                        if(c!='\t')
                        {
                            buf2[hmtd]=c;
                            hmtd++;
                            if(hmtd>h2)
                            {
                                h2=hmtd;
                            }
                        }
                        else
                        {
                            int ile=0;
                            if(buf2[hmtd]=='\0')
                            {
                                ile++;
                            }
                            buf2[hmtd]=' ';
                            if(buf2[hmtd+1]=='\0')
                            {
                                ile++;
                            }
                            buf2[hmtd+1]=' ';
                            if(buf2[hmtd+2]=='\0')
                            {
                                ile++;
                            }
                            buf2[hmtd+2]=' ';
                            if(buf2[hmtd+3]=='\0')
                            {
                                ile++;
                            }
                            buf2[hmtd+3]=' ';
                            hmtd+=4;
                            if(hmtd>h2)
                            {
                                h2=hmtd;
                            }
                        }
                    }
                    else
                    {
                        obs_ins(buf2,&hmtd,&h2,c);
                    }
                }
            }
            if(flaghis&&(incomf>=10000))
            {
                break;
            }
            else if(!flaghis&&(hmtd>=10000))
            {
                break;
            }
        }
        if(!flaghis)
        {
            strcpy(comf,buf2);
            flaghis=1;
        }
        printf("\n");
        tcsetattr(0,0,&o);
        i=0;
        aq1(buf2,comf,&i,1,&valpipe);
        i=0;
        if(!valpipe)
        {
            while(i<strlen(com))
            {
                if(comf[i]!=' ')
                {
                    break;
                }
                i++;
            }
            if((i==strlen(comf))||(comf[i]=='\n'))
            {
                continue;
            }
            in=0;
            while(i<strlen(comf))
            {
                if((comf[i]!='>')&&(comf[i]!='<'))
                {
                    if(((comf[i]=='1')||(comf[i]=='2')||(comf[i]=='&'))&&((i+1<strlen(comf))&&(comf[i+1]=='>')))
                    {
                        i++;
                        continue;
                    }
                    com[in]=comf[i];
                    in++;
                    com[in]='\0';
                    i++;
                }
                else
                {
                    if((comf[i]=='>')&&(i>0)&&(comf[i<1]!='2'))
                    {
                        ifr=0;
                    }
                    dupp(comf,&i);
                    while(i<strlen(comf))
                    {
                        if(comf[i]!=' ')
                        {
                            break;
                        }
                        i++;
                    }
                }

            }
            if(ifcdp)
            {
                continue;
            }
            j=0;
            i=0;
            while((j<60)&&(i<strlen(com)))
            {
                in=0;
                h2=1;
                memset(buf2,0,10000*sizeof(buf2[0]));
                while(i<strlen(com))
                {
                    if(com[i]==' ')
                    {
                        break;
                    }
                    aq1(buf2,com,&i,0,&h1);
                }
                while(i<strlen(com))
                {
                    if(com[i]!=' ')
                    {
                        break;
                    }
                    i++;
                }
                if(strcmp(buf2,"-fpath")!=0)
                {
                    strcpy(arg[j],buf2);
                    if((strcmp(arg[0],"cp")==0)&&(strcmp(arg[j],"-r")==0))
                    {
                        incpr=j;
                        flagcpr=1;
                    }
                    j++;
                }
                else
                {
                    if(h2)
                    {
                        flagpath=0;
                    }
                    else
                    {
                        strcpy(arg[j],buf2);
                        if((strcmp(arg[0],"cp")==0)&&(strcmp(arg[j],"-r")==0))
                        {
                            flagcpr=1;
                        }
                        j++;
                    }
                }
            }
            ifd=1;
            if((strcmp(arg[0],"cd")==0)&&flagpath)
            {
                his=fopen(hisp,"a");
                fputs(comf,his);
                fputc('\n',his);
                fclose(his);
                ifd=0;
                getcwd(t2,10000);
                if(j==1)
                {
                    chdir(getenv("HOME"));
                    strcpy(t1,t2);
                }
                else if(j==2)
                {
                    if(strcmp(arg[1],"-")==0)
                    {
                        if(strlen(t1)==0)
                        {
                            h1=dup(1);
                            dup2(dup(2),1);
                            printf("No such last directory\n");
                            dup2(h1,1);
                        }
                        else
                        {
                            chdir(t1);
                            strcpy(t1,t2);
                        }
                    }
                    else if(chdir(arg[1])!=0)
                    {
                        perror("The following error occurred: ");
                    }
                    else
                    {
                        strcpy(t1,t2);
                    }
                }
                else
                {
                    printf("The following error occurred: too many arguments\n");
                }
            }
            if((strcmp(arg[0],"exit")==0)&&(flagpath))
            {
                his=fopen(hisp,"a");
                fputs(comf,his);
                fputc('\n',his);
                fclose(his);
                if(j==1)
                {
                    tcsetattr(0,0,&o);
                    exit(0);
                }
                else if(j==2)
                {
                    int a=atoi(arg[1]);
                    tcsetattr(0,0,&o);
                    exit(a);
                }
                else
                {
                    printf("The following error occurred: too many arguments\n");
                }
            }
            if((strcmp(arg[0],"history")==0)&&(flagpath))
            {
                if(j==1)
                {
                    his=fopen(hisp,"a");
                    fputs(comf,his);
                    fputc('\n',his);
                    fclose(his);
                    ifd=0;
                    hiss=fopen(hisp,"r");
                    if(hiss!=NULL)
                    {
                        memset(buf2,0,10000*sizeof(buf2[0]));
                        h3=fgets(buf2,10000,hiss);
                        if(h3!=NULL)
                        {
                            i=1;
                            printf("%i ",i);
                        }
                        while(h3!=NULL)
                        {
                            printf("%s",buf2);
                            i++;
                            h3=fgets(buf2,10000,hiss);
                            if(h3!=NULL)
                            {
                                printf("%i ",i);
                            }
                        }
                        fclose(hiss);
                    }
                    else
                    {
                        perror("The following error occurred: ");
                    }
                }
                if(j==2)
                {
                    if(strcmp(arg[1],"-c")==0)
                    {
                        ifd=0;
                        if(remove(hisp)!=0)
                        {
                            perror("The following error occurred: ");
                        }
                    }
                    else
                    {
                        h1=dup(1);
                        dup2(dup(2),1);
                        printf("Bad input. Type \"help\" to see how you can use history\n");
                        dup2(h1,1);
                    }
                }
                else if(j>2)
                {
                    h1=dup(1);
                    dup2(dup(2),1);
                    printf("To many arguments\n");
                    dup2(h1,1);
                }
            }
            if((strcmp(arg[0],"tree")==0)&&flagpath)
            {
                his=fopen(hisp,"a");
                fputs(comf,his);
                fputc('\n',his);
                fclose(his);
                if(j<=2)
                {
                    ifd=0;
                    int d1=0;
                    int f1=0;
                    int bi=1;
                    if(j==2)
                    {
                        if(arg[1][0]!='-')
                        {
                            if(ifr)
                            {
                                printf("\033[1;34m%s\033[0m",arg[1]);
                            }
                            else
                            {
                                printf("%s",arg[1]);
                            }
                            tree(arg[1],0,tt,&d1,&f1,&ifr);
                        }
                        else
                        {
                            bi=0;
                            h1=dup(1);
                            dup2(dup(2),1);
                            printf("Bad input. Type \"help\" to see how you can use history\n");
                            dup2(h1,1);
                        }
                    }
                    else if(j==1)
                    {
                        if(ifr)
                        {
                            printf("\033[1;34m.\033[0m");
                        }
                        else
                        {
                            printf(".");
                        }
                        tree(".",0,tt,&d1,&f1,&ifr);
                    }
                    if(bi)
                    {
                        printf("\n\n");
                        if((d1>1)||(d1==0))
                        {
                            printf("%i directories, ",d1);
                        }
                        else
                        {
                            printf("%i directory, ",d1);
                        }
                        if((f1>1)||(f1==0))
                        {
                            printf("%i files\n",f1);
                        }
                        else
                        {
                            printf("%i file\n",f1);
                        }
                        printf("\n");
                    }
                }
                else
                {
                    ifd=0;
                    printf("too many arguments. Tu use tree from path use -fpath argument\n");
                }
            }
            if((strcmp(arg[0],"cp")==0)&&flagpath)
            {
                his=fopen(hisp,"a");
                fputs(comf,his);
                fputc('\n',his);
                fclose(his);
                if(j==3)
                {
                    ifd=0;
                    int tf[6];
                    whatis(arg[1],tf);
                    if(!tf[1])
                    {
                        _mkdir(arg[2]);
                        copy_file(arg[1],arg[2]);
                    }
                    else
                    {
                        int h1=dup(1);
                        dup2(dup(2),1);
                        printf("To copy directory use -r argument\n");
                        dup2(h1,1);
                    }
                }
                if((j==4)&&flagcpr)
                {
                    int in1;
                    int in2;
                    if(incpr==1)
                    {
                        in1=2;
                        in2=3;
                    }
                    else if(incpr==2)
                    {
                        in1=1;
                        in2=3;
                    }
                    else
                    {
                        in1=1;
                        in2=2;
                    }
                    int tf[6];
                    whatis(arg[in1],tf);
                    if(tf[1])
                    {
                        ifd=0;
                        char f1[10000];
                        char f2[10000];
                        char f3[10000];
                        memset(f1,0,10000*sizeof(f1[0]));
                        memset(f2,0,10000*sizeof(f2[0]));
                        memset(f3,0,10000*sizeof(f3[0]));
                        if(arg[in2][0]!='/')
                        {
                            memset(buf2,0,10000*sizeof(buf2[0]));
                            getcwd(buf2,10000);
                            if(buf2[strlen(buf2)-1]!='/')
                            {
                                strcat(buf2,"/");
                            }
                            strcat(buf2,arg[in2]);
                            strcpy(f2,buf2);
                        }
                        else
                        {
                            strcpy(f2,arg[in2]);
                        }
                        if((strcmp(arg[in1],".")==0)||(strcmp(arg[in1],"./")==0))
                        {
                            getcwd(f1,10000);
                        }
                        else
                        {
                            strcpy(f1,arg[in1]);
                        }
                        if(arg[in2][strlen(arg[in2]-1)]!='/')
                        {
                            strcat(arg[in2],"/");
                        }
                        memset(buf1,0,10000*sizeof(buf2[0]));
                        i=0;
                        in=0;
                        while(i<strlen(arg[in2]))
                        {
                            if(f2[i]!=buf2[i])
                            {
                                buf1[in]=f2[i];
                                in++;
                                buf1[in]='\0';
                            }
                            i++;
                        }
                        in=0;
                        i=1;
                        while(i<strlen(buf1))
                        {
                            if(buf1[i]!='/')
                            {
                                f3[in]=buf1[i];
                                in++;
                                f3[in]='\0';
                            }
                            else
                            {
                                break;
                            }
                            i++;
                        }
                        memset(buf1,0,10000*sizeof(buf1[0]));
                        strcpy(buf1,buf2);
                        strcat(buf1,"/");
                        strcat(buf1,f3);
                        strcpy(f3,buf1);
                        cpr(f1,f1,f2,f3);
                    }
                    else
                    {
                        ifd=0;
                        _mkdir(arg[in2]);
                        copy_file(arg[in1],arg[in2]);
                    }
                }
                else if(j==2)
                {
                    ifd=0;
                    printf("not enough arguments\n");
                }
                else if(j>4)
                {
                    ifd=0;
                    printf("too many arguments or unsupported arguemnt. Tu use cp from path use -fpath argument\n");
                }
            }
            if((strcmp(arg[0],"help")==0)&&flagpath)
            {
                his=fopen(hisp,"a");
                fputs(comf,his);
                fputc('\n',his);
                fclose(his);
                ifd=0;
                printf("Microshell created by Wojciech Bernat, AMU student\n");
                printf("program capabilities:\n");
                printf("-launching any program from PATH\n");
                printf("The maximum number of arguments is 60\n");
                printf("If you want, you can use some commands in the pipe\n");
                printf("Then you will only use programs from PATH\n");
                printf("-cd (works like in bash)\n");
                printf("-cp with -r argument\nIf you want to use cp from PATH, use the -fpath argument\n");
                printf("-tree\n");
                printf("-exit\nIf you want to use exit with exit code, type it after the command\n");
                printf("-history\nIf you want to use a command from the history, select it with the arrows\n");
                printf("If you want to redirect input or output you can do it just like in bash\n");
                printf("<< is not supported\n");
            }
        }
        if(valpipe||ifd)
        {
            his=fopen(hisp,"a");
            fputs(comf,his);
            fputc('\n',his);
            fclose(his);
            char **args=malloc(101*sizeof(*args));
            valpipe++;
            int pipe1[2];
            int pipe2[2];
            pipe(pipe1);
            pipe(pipe2);
            i=0;
            ife=1;
            int ifb=1;
            int ifr=0;
            int ifbr=0;
            int ifp=1;
            while(valpipe&&ife)
            {
                if(!ife)
                {
                    if(ifp)
                    {
                        pipe(pipe2);
                    }
                    else
                    {
                        pipe(pipe1);
                    }
                }
                j=0;
                while((j<60)&&(i<strlen(comf)))
                {
                    if(comf[i]=='|')
                    {
                        i++;
                        break;
                    }
                    args[j]=malloc(10000*sizeof(args));
                    memset(args[j],0,10000*sizeof(args[j][0]));
                    while(i<strlen(comf))
                    {
                        if(comf[i]!=' ')
                        {
                            break;
                        }
                        i++;
                    }
                    in=0;
                    flag=0;
                    ifa=0;
                    ifq=0;
                    while(i<strlen(comf))
                    {
                        if((comf[i]=='|')&&!flag)
                        {
                            break;
                        }
                        if((comf[i]=='\'')&&!flag)
                        {
                            flag=1;
                            ifa=1;
                            i++;
                            continue;
                        }
                        if((comf[i]=='"')&&!flag)
                        {
                            flag=1;
                            ifq=1;
                            i++;
                            continue;
                        }
                        if((comf[i]=='\'')&&flag&&ifa)
                        {
                            flag=0;
                            ifa=0;
                            i++;
                            continue;
                        }
                        if((comf[i]=='"')&&flag&&ifq)
                        {
                            flag=0;
                            ifq=0;
                            i++;
                            continue;
                        }
                        if(((comf[i]=='>')||((i+1<strlen(comf))&&(comf[i+1]=='>')))&&!flag&&(comf[i]!=' '))
                        {
                            if((comf[i]=='1')||(comf[i]=='>'))
                            {
                                if(i>0)
                                {
                                    if((comf[i]=='>')&&(comf[i-1]!='2'))
                                    {
                                        ife=0;
                                    }
                                }
                                else
                                {
                                    ife=0;
                                }
                            }
                            if(((comf[i]=='>')&&((i+1<strlen(comf))&&(comf[i+1]=='>')))||(comf[i]=='>'))
                            {
                                ifr=1;
                                dupp(comf,&i);
                                while(i<strlen(comf))
                                {
                                    if(comf[i]!=' ')
                                    {
                                        break;
                                    }
                                    i++;
                                }
                                i--;
                            }
                            else
                            {
                                ifr=1;
                                i++;
                                dupp(comf,&i);
                                while(i<strlen(comf))
                                {
                                    if(comf[i]!=' ')
                                    {
                                        break;
                                    }
                                    i++;
                                }
                                i--;
                            }
                        }
                        else if(comf[i]=='<')
                        {
                            if(!ifb)
                            {
                                ifbr=1;
                                break;
                            }
                            else
                            {
                                dupp(comf,&i);
                                while(i<strlen(comf))
                                {
                                    if(comf[i]!=' ')
                                    {
                                        break;
                                    }
                                    i++;
                                }
                                i--;
                            }
                        }
                        else
                        {
                            char buf3[10000];
                            strcpy(buf3,args[j]);
                            if((comf[i]!=' ')||flag)
                            {
                                if(comf[i]!='\n')
                                {
                                    if((comf[i]!='~')||flag||((i>0)&&(comf[i-1]=='/')))
                                    {
                                        args[j][in]=comf[i];
                                        in++;
                                    }
                                    else if((i>0)&&(comf[i-1]!='/'))
                                    {
                                        strcpy(buf1,getenv("HOME"));
                                        strcat(args[j],buf1);
                                        in+=strlen(buf1);
                                    }
                                    args[j][in]='\0';
                                }
                            }
                            else
                            {
                                break;
                            }
                            if((strcmp(args[j],"-fpath")==0)&&!flag)
                            {
                                if(!flagpath)
                                {
                                    in=0;
                                    memset(args[j],0,10000*sizeof(args[j][0]));
                                    i++;
                                    while(i<strlen(comf))
                                    {
                                        if(comf[i]!=' ')
                                        {
                                            break;
                                        }
                                        i++;
                                    }
                                    if(i!=strlen(comf))
                                    {
                                        i--;
                                    }
                                }
                            }
                        }
                        i++;
                    }
                    if((i==strlen(comf))&&(strlen(args[j])==0))
                    {
                        free(args[j]);
                        args[j]=NULL;
                    }
                    else if(strlen(args[j])==0)
                    {
                        free(args[j]);
                        args[j]=NULL;
                    }
                    j++;
                }
                if(i==strlen(comf))
                {
                    ife=0;
                }
                if(args[j-1]!=NULL)
                {
                    args[j]=NULL;
                }
                if(args[0]==NULL)
                {
                    h1=dup(1);
                    dup2(dup(2),1);
                    printf("unexpected syntax error at '|'\n");
                    dup2(h1,1);
                    break;
                }
                if(!ifbr)
                {
                    if(ifb)
                    {
                        if((pid=fork())==0)
                        {
                            if(!ifr&&ife)
                            {
                                dup2(pipe1[1],1);
                            }
                            close(pipe1[0]);
                            close(pipe1[1]);
                            if(execvp(args[0],args)==-1)
                            {
                                perror("The following error occurred: ");
                                ife=0;
                                ifbr=1;
                            }
                            exit(0);
                        }
                        ifb=0;
                    }
                    else
                    {
                        if(ifp)
                        {
                            close(pipe1[1]);
                            if((pid=fork())==0)
                            {
                                dup2(pipe1[0],0);
                                if(!ifr&&ife)
                                {
                                    dup2(pipe2[1],1);
                                }
                                close(pipe2[0]);
                                close(pipe2[1]);
                                if(execvp(args[0],args)==-1)
                                {
                                    perror("The following error occurred: ");
                                    ifbr=1;
                                    ife=0;
                                }
                                exit(0);
                            }
                            ifp=0;
                        }
                        else
                        {
                            close(pipe2[1]);
                            if((pid=fork())==0)
                            {
                                dup2(pipe2[0],0);
                                if(!ifr&&ife)
                                {
                                    dup2(pipe1[1],1);
                                }
                                close(pipe1[0]);
                                close(pipe1[1]);
                                if(execvp(args[0],args)==-1)
                                {
                                    perror("The following error occurred: ");
                                    ifbr=1;
                                    ife=0;
                                }
                                exit(0);
                            }
                            ifp=1;
                        }
                    }
                    wait(NULL);
                    valpipe--;
                }
                h1=0;
                while(h1<j)
                {
                    free(args[h1]);
                    h1++;
                }
                if(ifbr)
                {
                    break;
                }

            }
            free(args);
            if(ifbr)
            {
                h1=dup(1);
                dup2(dup(2),1);
                printf("Error, probably you try to change input inside pipe what you can't do in this microshell\n");
                dup2(h1,1);
            }
        }
    }
    return 0;
}
void _mkdir(char *p)
{
    char a[10000];
    char b[10000];
    memset(a,0,10000*sizeof(a[0]));
    memset(b,0,10000*sizeof(b[0]));
    int in=0;
    int i=0;
    while(i<strlen(p))
    {
        if(p[i]!='/')
        {
            a[in]=p[i];
            in++;
            a[in]='\0';
        }
        else
        {
            while((i<strlen(p))&&(p[i]=='/'))
            {
                i++;
            }
            i--;
            a[in]=p[i];
            a[in+1]='\0';
            in=0;
            strcat(b,a);
            if(access(b,F_OK)!=0)
            {
                mkdir(b,0777);
            }
            in=0;
            memset(a,0,10000*sizeof(a[0]));
        }
        i++;
    }
}
void copy_file(char *file1, char *file2)
{
    int tf[7];
    whatis(file1,tf);
    if(tf[2])
    {
        char buf[10000];
        memset(buf,0,10000*sizeof(buf[0]));
        readlink(file1,buf,10000);
        symlink(buf,file2);
    }
    else
    {
        FILE *f1=fopen(file1,"r");
        if(f1!=NULL)
        {
            struct stat ps;
            stat(file1,&ps);
            creat(file2,ps.st_mode);
        }
        FILE *f2=fopen(file2,"w");
        if((f1!=NULL)&&(f2!=NULL))
        {
            char t=fgetc(f1);
            while(t!=EOF)
            {
                fputc(t,f2);
                t=fgetc(f1);
            }
            fclose(f1);
            fclose(f2);
        }
        else
        {
            perror("The following error occurred: ");
        }
    }
}
void cpr(char *fr, char *f1, char *f2, char *f3)
{
    struct dirent **d;
    int val=scandir(fr,&d,NULL,alphasort);
    if(val!=-1)
    {
        char dir1[10000];
        memset(dir1,0,10000*sizeof(dir1[0]));
        strcat(dir1,f2);
        char t[10000];
        memset(t,0,10000*sizeof(t[0]));
        char dir2[10000];
        memset(dir2,0,10000*sizeof(dir2[0]));
        int in=0;
        int flag=1;
        int i=0;
        while(i<strlen(fr))
        {
            if(flag)
            {
                t[i]=fr[i];
                if(strcmp(f1,t)==0)
                {
                    flag=0;
                }
            }
            else
            {
                dir2[in]=fr[i];
                in++;
                dir2[in]='\0';
            }
            i++;
        }
        memset(t,0,10000*sizeof(t[0]));
        if(dir1[strlen(dir1)-1]!='/')
        {
            strcat(dir1,"/");
        }
        strcat(dir1,dir2);
        strcat(dir1,"/");
        _mkdir(dir1);
        i=0;
        strcpy(t,dir1);
        while(i<val)
        {
            strcpy(dir1,t);
            char fn[10000];
            char fp[10000];
            strcpy(fp,fr);
            if(fp[strlen(fp)-1]!='/')
            {
                strcat(fp,"/");
            }
            strcpy(fn,d[i]->d_name);
            free(d[i]);
            strcat(fp,fn);
            int tf[7];
            whatis(fp,tf);
            if(((strcmp(fn,".")==0)||(strcmp(fn,"..")==0))&&(tf[1]))
            {
                i++;
                continue;
            }
            if(dir1[strlen(dir1)-1]!='/')
            {
                strcat(dir1,"/");
            }
            strcat(dir1,fn);
            strcat(dir1,"\0");
            if(!tf[1])
            {
                copy_file(fp,dir1);
            }
            else
            {
                if(strcmp(fp,f3)!=0)
                {
                    char h1[10000];
                    char h2[10000];
                    memset(h1,0,10000*sizeof(h1[0]));
                    memset(h2,0,10000*sizeof(h2[0]));
                    strcpy(h1,fr);
                    strcpy(h2,"/");
                    strcat(h2,fn);
                    strcat(h1,h2);
                    cpr(h1,f1,f2,f3);
                }
            }
            i++;
        }
        free(d);
    }
    else
    {
        perror("The following error occurred: ");
    }
}
void aq1(char *t1, char *t2, int *j, int ifc, int *c)
{
    int in=0;
    int flag=0;
    int ifa=0;
    int ifq=0;
    while(*j<strlen(t2))
    {
        if(!flag&&(t2[*j]=='\''))
        {
            flag=1;
            ifa=1;
            *j+=1;
            continue;
        }
        if(!flag&&(t2[*j]=='"'))
        {
            flag=1;
            ifq=1;
            *j+=1;
            continue;
        }
        if(flag&&ifa&&(t2[*j]=='\''))
        {
            flag=0;
            ifa=0;
            *j+=1;
            continue;
        }
        if(flag&&ifq&&(t2[*j]=='"'))
        {
            flag=0;
            ifq=0;
            *j+=1;
            continue;
        }
        if(!ifc)
        {
            if(flag||(t2[*j]!=' '))
            {
                if(t2[*j]!='\n')
                {
                    if((t2[*j]!='~')||flag||((*j>0)&&(t2[*j-1]=='/')))
                    {
                        t1[in]=t2[*j];
                        in++;
                    }
                    else if((*j>0)&&(t2[*j-1]!='/'))
                    {
                        char buf[10000];
                        strcpy(buf,getenv("HOME"));
                        strcat(t1,buf);
                        in+=strlen(buf);
                    }
                    t1[in]='\0';
                }
                *j+=1;
            }
            else if(t2[*j]==' ')
            {
                break;
            }
        }
        else
        {
            if((t2[*j]=='|')&&(!flag))
            {
                *c+=1;
            }
            *j+=1;
        }
    }
}
void dupp(char *t, int *j)
{
    if(t[*j]=='>')
    {
        int fa=0;
        int fo=0;
        int fe=1;
        int fw;
        int ts1;
        int ts2;
        if((*j>0)&&(t[*j-1]=='2')&&(*j+1<strlen(t))&&(t[*j+1]!='&'))
        {
            fw=2;
        }
        else if((*j>0)&&(t[*j-1]=='&'))
        {
            fw=3;
        }
        else if((*j>0)&&(t[*j-1]!='2')&&(*j+1<strlen(t))&&(t[*j+1]=='&'))
        {
            fw=3;
            *j+=1;
        }
        else if(!((*j>0)&&(t[*j-1]=='2')&&(*j+1<strlen(t))&&(t[*j+1]=='&')&&(*j+2<strlen(t))&&(t[*j+2]=='1')))
        {
            fw=1;
        }
        else
        {
            fw=4;
        }
        if((*j>0)&&(t[*j-1]=='1'))
        {
            fo=1;
        }
        if((*j+1<strlen(t))&&(t[*j+1]=='>'))
        {
            *j+=2;
            fa=1;
        }
        else
        {
            *j+=1;
        }
        while(*j<strlen(t))
        {
            if(t[*j]!=' ')
            {
                break;
            }
            *j+=1;
        }
        char dir[1000];
        int h1=0;
        aq1(dir,t,&*j,0,&h1);
        if(strlen(dir)==0)
        {
            h1=dup(1);
            dup2(dup(2),1);
            printf("unexpected syntax error at '>'\n");
            dup2(h1,1);
            fo=0;
            fe=0;
            ifcdp=1;
        }
        if(fo)
        {
            if(strcmp(dir,"&2")==0)
            {
                dup2(dup(1),2);
                fe=0;
            }
        }
        if(fe)
        {
            _mkdir(dir);
            if(fw==1)
            {
                if(fa)
                {
                    ts1=open(dir, O_CREAT | O_WRONLY | O_APPEND,0666);
                }
                else
                {
                    ts1=open(dir, O_CREAT | O_WRONLY | O_TRUNC, 0666);
                }
                dup2(ts1,1);
                close(ts1);
            }
            else if(fw==2)
            {
                if(fa)
                {
                    ts2=open(dir, O_CREAT | O_WRONLY | O_APPEND,0666);
                }
                else
                {
                    ts2=open(dir, O_CREAT | O_WRONLY | O_TRUNC, 0666);
                }
                dup2(ts2,2);
                close(ts2);
            }
            else if(fw==3)
            {
                if(fa)
                {
                    ts1=open(dir, O_CREAT | O_WRONLY | O_APPEND,0666);
                }
                else
                {
                    ts1=open(dir, O_CREAT | O_WRONLY | O_TRUNC, 0666);
                }
                dup2(ts1,1);
                dup2(ts1,2);
                close(ts1);
            }
            else if(fw==4)
            {
                dup2(dup(1),2);
            }
        }
    }
    else if(t[*j+1]!='<')
    {
        int to;
        *j+=1;
        while(*j<strlen(t))
        {
            if(t[*j]!=' ')
            {
                break;
            }
            *j+=1;
        }
        char dir[1000];
        int h1=0;
        aq1(dir,t,&*j,0,&h1);
        to=open(dir, O_RDONLY);
        if(to!=-1)
        {
            dup2(to,0);
            close(to);
        }
        else
        {
            perror("The following error occurred: ");
            ifcdp=1;
        }
    }
    else
    {
        int h1=dup(1);
        if(ifw)
        {
            dup2(s1,1);
            printf("<< is not supported\n");
            dup2(h1,1);
            ifw=0;
        }
        *j+=2;
        while(*j<strlen(t))
        {
            if(t[*j]!=' ')
            {
                break;
            }
            *j+=1;
        }
        char dir[1000];
        h1=0;
        aq1(dir,t,&*j,0,&h1);
    }
}
void tree(char *fr, int g, int *t, int *valdir, int *valfile, int *ifr)
{
    struct dirent **dir;
    int val=scandir(fr,&dir,NULL,alphasort);
    if(val!=-1)
    {
        int i=0;
        while(i<val)
        {
            char fn[10000];
            char fp[10000];
            memset(fn,0,10000*sizeof(fn[0]));
            memset(fp,0,10000*sizeof(fp[0]));
            strcpy(fp,fr);
            if(fp[strlen(fp)-1]!='/')
            {
                strcat(fp,"/");
            }
            strcpy(fn,dir[i]->d_name);
            free(dir[i]);
            if(strcmp(fn,"1")==0)
            {
                printf(" \b");
            }
            strcat(fp,fn);
            int tf[6];
            whatis(fp,tf);
            if(((strcmp(fn,".")==0)||(strcmp(fn,"..")==0))&&(tf[1]))
            {
                i++;
                continue;
            }
            printf("\n");
            if(tf[1])
            {
                *valdir+=1;
            }
            else
            {
                *valfile+=1;
            }
            int o=0;
            while(o<g)
            {
                if(t[o])
                {
                    printf("\u2502   ");
                }
                else
                {
                    printf("    ");
                }
                o++;
            }
            if(i==val-1)
            {
                printf("\u2514\u2500\u2500 ");
                t[g]=0;
            }
            else
            {
                printf("\u251C\u2500\u2500 ");
            }
            if(*ifr)
            {
                if((!access(fp,X_OK)))
                {
                    printf("\033[1;32m");
                }
                if(tf[1])
                {
                    printf("\033[1;34m");
                }
                if(tf[2])
                {
                    printf("\033[0;36m");
                }
                if(tf[3]||tf[4]||tf[5])
                {
                    printf("\033[0;33m");
                }
                printf("%s \033[0m",fn);
            }
            else
            {
                printf("%s ",fn);
            }
            if(tf[1]&&!tf[2])
            {
                tree(fp,g+1,t,&*valdir,&*valfile,&*ifr);
            }
            else if(tf[2])
            {
                char buf1[10000];
                char buf2[10000];
                memset(buf1,0,10000*sizeof(buf1[0]));
                memset(buf2,0,10000*sizeof(buf2[0]));
                readlink(fp,buf1,10000);
                if(buf1[0]!='/')
                {
                    strcpy(buf2,fr);
                    if(buf2[strlen(buf2)-1]!='/')
                    {
                        strcat(buf2,"/");
                    }
                    strcat(buf2,buf1);
                }
                else
                {
                    strcpy(buf2,buf1);
                }
                int tff[6];
                whatis(buf2,tff);
                printf(" -> ");
                if(*ifr)
                {
                    if((!access(buf2,X_OK)))
                    {
                        printf("\033[1;32m");
                    }
                    if(tff[1])
                    {
                        printf("\033[1;34m");
                    }
                    if(tff[2])
                    {
                        printf("\033[0;36m");
                    }
                    if(tff[3]||tff[4]||tff[5])
                    {
                        printf("\033[0;33m");
                    }
                }
                printf("%s ",buf1);
                if(*ifr)
                {
                    printf("\033[0m");
                }
            }
            i++;
        }
        free(dir);
        t[g]=1;
    }
    else
    {
        printf("[error opening dir]");
    }
}
void obs_ins(char *nap, int *innap, int *h, char c)
{
    int i=0;
    int hm=0;
    char buf3[10000];
    char buf4[10000];
    memset(buf3,0,10000*sizeof(buf3[0]));
    memset(buf4,0,10000*sizeof(buf4[0]));
    while(i<*innap)
    {
        buf3[i]=nap[i];
        i++;
    }
    if(c!='\t')
    {
        buf3[i]=c;
        *innap+=1;
    }
    else
    {
        strcat(buf3,"    ");
        *innap+=4;
    }
    int h4=0;
    while(i<*h)
    {
        buf4[h4]=nap[i];
        i++;
        h4++;
    }
    strcat(buf3,buf4);
    strcpy(nap,buf3);
    if(c!='\t')
    {
        *h+=1;
    }
    else
    {
        *h+=4;
    }
    while(*innap<*h)
    {
        hm++;
        printf("%c",nap[*innap]);
        *innap+=1;
    }
    i=0;
    while(i<hm)
    {
        *innap-=1;
        printf("\b");
        i++;
    }
}
