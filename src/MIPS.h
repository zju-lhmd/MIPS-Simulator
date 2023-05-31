#include<iostream>
#include<string>
#include<sstream>
#include<map>
#include<cmath>
#include<stack>
#include<regex>

using namespace std;

/*
所有的二进制数均用string存储
*/

class Binary{
    /*
使用:已定义Binary_change，若使用功能函数Binary_change.function即可
    若要使用二进制加减先申明类再使用重载的加减
*/
public:
    string binary;//存放二进制原码
    Binary(){
        binary="";
    }
    Binary(int len){
        string zero(len,'0');
        binary=zero;
    }
    Binary(string num){
        binary=num;
    }
    string Binary2Complement(string num){
        /*
        原码转补码
        num:二进制数
        */
        if(num[0]=='0')return num;
        for(int i=1;i<(int)num.size();i++)
            num[i]='1'-(num[i]-'0');
        int len=num.size()-1;
        num[len]++;
        while(num[len]=='2'){
            num[len]='0';
            len--;
            if(len==-1)break;
            num[len]++;
        }
        return num;
    }
    string Complement2Binary(string num){
        /*
        补码转原码
        num:二进制数
        */
        if(num[0]=='0')return num;
        for(int i=1;i<(int)num.size();i++)
            num[i]='1'-(num[i]-'0');
        int len=num.size()-1;
        num[len]--;
        while(num[len]<'0'){
            num[len]='1';
            len--;
            if(len==-1)break;
            num[len]--;
        }
        return num;
    }
    string Int2Binary(int num,int len){
        /*
        十进制整数转二进制
        num:十进制数
        len:二进制数长度
        */
        string num_binary(len,'0');
        if(num<0){
            num_binary[0]='1';
            num=-num;
        }
        for(int i=1;i<len;i++){
            int x=pow(2,len-i-1);
            if(num>=x){
                num_binary[i]='1';
                num-=x;
            }
        }
        return num_binary;
    }
    int Binary2Int(string num,int typ){
        /*
        二进制转十进制
        typ=0无符号 typ=1有符号
        */
        int res=0,flag=1;
        int len=num.size();
        if(typ==1&&num[0]=='1'){
            flag=-1;
            int k=len-1;
            while(num[k]=='0')k--;
            num[k]='0';
            for(int i=k+1;i<len;i++)
                num[i]='1';
            for(int i=0;i<len;i++)num[i]='1'-(num[i]-'0');
        }
        for(int i=0;i<len;i++)
            res=res*2+num[i]-'0';
        return res*flag;
    }
    string Int2Binary_unsigned(int num,int len){
        /*
        十进制整数转无符号二进制
        num:十进制数
        len:二进制数长度
        */
        string num_binary(len,'0');
        if(num<0)num=-num;
        for(int i=0;i<len;i++){
            int x=pow(2,len-i-1);
            if(num>=x){
                num_binary[i]='1';
                num-=x;
            }
        }
        return num_binary;
    }
    string Int2Complement(int num,int len){
        /*
        十进制整数转二进制补码
        num:十进制数
        len:二进制数长度
        */
        return Binary2Complement(Int2Binary(num,len));
    }
    void Print(){
        cout<<binary<<endl;
    }
    string operator + (const string &num){
        /*
        重载二进制加法
        若为复数 转化为补码再相加
        若长度不同转化为长度更长的
        */
        string num1=binary;
        string num2=num;
        if(num1[0]=='1')num1=Binary2Complement(num1);
        if(num2[0]=='1')num2=Binary2Complement(num2);
        if(num1.size()<num2.size())swap(num1,num2);
        int len=num1.size();
        if(num1.size()!=num2.size()){
            int p=(num2[0]=='1');
            num2[0]='0';
            string zero(len-num2.size(),'0');
            num2=zero+num2;
            num2[0]='0'+p;
        }
        string res(len,'0');
        for(int i=len-1;i>=0;i--){
            int x=num1[i]-'0'+num2[i]-'0'+res[i]-'0';
            res[i]=x%2+'0';
            if(i)res[i-1]+=x/2;
        }
        if(res[0]=='1')res=Complement2Binary(res);
        return res;
    }
    string operator - (const string &num){
        /*
        重载二进制减法
        将减数取反 调用加法
        */
        string num2=num;
        num2[0]='1'-(num2[0]-'0');
        return *this+num2;
    }
}Binary_change;

class Float{
    /*
对于32位浮点数 1+8+23
使用:已定义Float_change，若使用功能函数Float_change.function即可
    若要使用float加减乘除先申明类再使用重载的加减乘除
*/
public:
    string float_num;//存放float二进制表示
    Float(){
        float_num="";
    }
    Float(string num){
        float_num=num;
    }
    Float(float num){
        float_num=float2binary(num);
    }
    string float2binary(float x){
        /*
        float转二进制
        x:存储的数
        */
        if(x == 0){
            return string(32,'0');
        }

        string num(1,'0');
        if(x<0){
            num[0]='1';
            x=-x;
        }
        int exponent=0;
        while(x<1){
            x=x*2;
            exponent--;
        }
        while(x>=2){
            x=x/2;
            exponent++;
        }
        num=num+Binary_change.Int2Binary_unsigned(exponent+127,8);
        x-=1;
        string fraction(23,'0');
        for(int i=0;i<23;i++){
            float y=pow(2,-i-1);
            if(x>=y){
                x-=y;
                fraction[i]='1';
            }
            if(x==0)break;
        }
        num=num+fraction;
        return num;
    }
    int Exponent(string x){//指数
        int exponent=0;
        for(int i=1;i<=8;i++)
            exponent=exponent*2+x[i]-'0';
        return exponent-127;
    }
    float Fraction(string x){//尾数
        float fraction=1;
        for(int i=9;i<32;i++)
            if(x[i]=='1')fraction+=pow(2,8-i);
        return fraction;
    }
    float binary2float(string x){
        /*
         二进制转float
        */
        int exponent=Exponent(x);
        float fraction=Fraction(x);
        return (x[0]=='1'?-1:1)*fraction*pow(2,exponent);
    }
    void Print(){
        cout<<float_num<<endl;
    }
    string operator + (const string &num){
        int e1=Exponent(float_num),e2=Exponent(num);
        string f1="01"+float_num.substr(9,23),f2="01"+num.substr(9,23);
        while(e1>e2){
            e2++;
            f1=f1+'0';
            f2='0'+f2;
        }
        while(e2>e1){
            e1++;
            f1='0'+f1;
            f2=f2+'0';
        }//统一指数
        f1=float_num[0]+f1;
        f2=num[0]+f2;//加符号位
        Binary res_f(f1);
        res_f=res_f+f2;//计算+
        res_f.Print();
        string res(1,'0');
        res[0]=res_f.binary[0];
        int k=1;
        while(res_f.binary[k]=='0')
            k++;
        if(k==(int)res_f.binary.length()){
            string zero(32,'0');
            return zero;
        }
        e1=e1+2-k;//k是1的位置 1后面是尾数 e1是指数
        string zero(32,'0');
        res_f.binary=res_f.binary+zero;
        res=res+Binary_change.Int2Binary_unsigned(e1+127,8)+res_f.binary.substr(k+1,23);
        return res;
    }
    string operator + (const float &num){
        return *this+float2binary(num);
    }
    string operator - (const string &num){
        string num1=num;
        num1[0]='1'-(num1[0]-'0');
        return *this+num1;
    }
    string operator - (const float &num){
        return *this-float2binary(num);
    }
    string operator * (const string &num){
        int e1=Exponent(float_num),e2=Exponent(num),e=e1+e2;
        string f1="1"+float_num.substr(9,23),f2="1"+num.substr(9,23);
        Binary res_f(52);
        for(int i=0;i<24;i++)
            if(f2[i]=='1'){
                string zero(23-i,'0');
                res_f.binary=res_f+("0"+f1+zero);
            }
        int k=1;
        while(res_f.binary[k]=='0')k++;
        e=e+5-k;
        string res(1,'0');
        res[0]=(float_num[0]!=num[0])+'0';
        res=res+Binary_change.Int2Binary_unsigned(e+127,8)+res_f.binary.substr(k+1,23);
        return res;
    }
    string operator * (const float &num){
        return *this*float2binary(num);
    }
    string operator / (const string &num){
        int e1=Exponent(float_num),e2=Exponent(num),e=e1-e2;
        string zero(24,'0'),f1="1"+float_num.substr(9,23)+zero,f2="01"+num.substr(9,23);
        string res_f(24,'0');
        for(int i=0;i<24;i++){
            Binary div("0"+f1.substr(0,i+24));
            div.binary=div-f2;
            if(div.binary[0]=='1')continue;
            res_f[i]='1';
            f1.replace(0,i+24,div.binary.substr(1,i+24));
        }
        int k=0;
        while(res_f[k]=='0')k++;
        e=e-k;
        string res(1,'0');
        res[0]=(float_num[0]!=num[0])+'0';
        res=res+Binary_change.Int2Binary_unsigned(e+127,8)+res_f.substr(k+1,23);
        return res;
    }
    string operator / (const float &num){
        return *this/float2binary(num);
    }
}Float_change;

class Double{
    /*
对于64位浮点数 1+11+52
使用:已定义Double_change，若使用功能函数Double_change.function即可
    若要使用double加减乘除先申明类再使用重载的加减乘除
*/
public:
    string double_num;//存放float二进制表示
    Double(){
        double_num="";
    }
    Double(string num){
        double_num=num;
    }
    Double(double num){
        double_num=double2binary(num);
    }
    string double2binary(double x){
        /*
        double转二进制
        x:存储的数
        */
        string num(1,'0');
        if(x<0){
            num[0]='1';
            x=-x;
        }
        int exponent=0;
        while(x<1){
            x=x*2;
            exponent--;
        }
        while(x>=2){
            x=x/2;
            exponent++;
        }
        num=num+Binary_change.Int2Binary_unsigned(exponent+1023,11);
        x-=1;
        string fraction(52,'0');
        for(int i=0;i<52;i++){
            float y=pow(2,-i-1);
            if(x>=y){
                x-=y;
                fraction[i]='1';
            }
            if(x==0)break;
        }
        num=num+fraction;
        return num;
    }
    int Exponent(string x){//指数
        int exponent=0;
        for(int i=1;i<=11;i++)
            exponent=exponent*2+x[i]-'0';
        return exponent-1023;
    }
    double Fraction(string x){//尾数
        double fraction=1;
        for(int i=12;i<64;i++)
            if(x[i]=='1')fraction+=pow(2,11-i);
        return fraction;
    }
    double binary2double(string x){
        /*
         二进制转double
        */
        int exponent=Exponent(x);
        double fraction=Fraction(x);
        return (x[0]=='1'?-1:1)*fraction*pow(2,exponent);
    }
    void Print(){
        cout<<double_num<<endl;
    }
    string operator + (const string &num){
        int e1=Exponent(double_num),e2=Exponent(num);
        string f1="01"+double_num.substr(12,52),f2="01"+num.substr(12,52);
        while(e1>e2){
            e2++;
            f1=f1+'0';
            f2='0'+f2;
        }
        while(e2>e1){
            e1++;
            f1='0'+f1;
            f2=f2+'0';
        }//统一指数
        f1=double_num[0]+f1;
        f2=num[0]+f2;//加符号位
        Binary res_f(f1);
        res_f=res_f+f2;//计算+
        string res(1,'0');
        res[0]=res_f.binary[0];
        int k=1;
        while(res_f.binary[k]=='0')
            k++;
        if(k==res_f.binary.length()){
            string zero(64,'0');
            return zero;
        }
        e1=e1+2-k;//k是1的位置 1后面是尾数 e1是指数
        string zero(52,'0');
        res_f.binary=res_f.binary+zero;
        res=res+Binary_change.Int2Binary_unsigned(e1+1023,11)+res_f.binary.substr(k+1,52);
        return res;
    }
    string operator + (const double &num){
        return *this+double2binary(num);
    }
    string operator - (const string &num){
        string num1=num;
        num1[0]='1'-(num1[0]-'0');
        return *this+num1;
    }
    string operator - (const double &num){
        return *this-double2binary(num);
    }
    string operator * (const string &num){
        int e1=Exponent(double_num),e2=Exponent(num),e=e1+e2;
        string f1="1"+double_num.substr(12,52),f2="1"+num.substr(12,52);
        Binary res_f(110);
        for(int i=0;i<53;i++)
            if(f2[i]=='1'){
                string zero(52-i,'0');
                res_f.binary=res_f+("0"+f1+zero);
            }
        int k=1;
        while(res_f.binary[k]=='0')k++;
        e=e+5-k;
        string res(1,'0');
        res[0]=(double_num[0]!=num[0])+'0';
        res=res+Binary_change.Int2Binary_unsigned(e+1023,11)+res_f.binary.substr(k+1,52);
        return res;
    }

    string operator * (const double &num){
        return *this*double2binary(num);
    }
    string operator / (const string &num){
        int e1=Exponent(double_num),e2=Exponent(num),e=e1-e2;
        string zero(53,'0'),f1="1"+double_num.substr(12,52)+zero,f2="01"+num.substr(12,52);
        string res_f(53,'0');
        for(int i=0;i<53;i++){
            Binary div("0"+f1.substr(0,i+53));
            div.binary=div-f2;
            if(div.binary[0]=='1')continue;
            res_f[i]='1';
            f1.replace(0,i+53,div.binary.substr(1,i+53));
        }
        int k=0;
        while(res_f[k]=='0')k++;
        e=e-k;
        string res(1,'0');
        res[0]=(double_num[0]!=num[0])+'0';
        res=res+Binary_change.Int2Binary_unsigned(e+1023,11)+res_f.substr(k+1,52);
        return res;
    }
    string operator / (const double &num){
        return *this/double2binary(num);
    }
}Double_change;

class Disassembly{
    /*
反汇编
instruct存反汇编的指令
instruct_binary 机器码的二进制
instruct_hex 机器码的十六进制
reg寄存器名字转五位二进制
reg_binary五位二进制转寄存器名字
使用:已定义disassembly
先调用disassembly.clear()清除上一次记录
调用disassembly.read(type,machine_code) 读入机器码 可以读入二进制或十六进制机器码
调用disassembly.solve()进行反汇编
调用disassembly.Print()输出mips代码
*/
public:
    vector<string>instruct;
    vector<string>instruct_binary;
    vector<string>instruct_hex;
    map<string,string>reg;
    map<string,string>reg_binary;

    map<int, string> labels; // 标签
    int label_id;

    Disassembly(){
        instruct.clear();
        instruct_binary.clear();
        instruct_hex.clear();
        reg_binary["00000"]="$zero";
        reg_binary["00001"]="$at";
        reg_binary["00010"]="$v0";
        reg_binary["00011"]="$v1";
        reg_binary["00100"]="$a0";
        reg_binary["00101"]="$a1";
        reg_binary["00110"]="$a2";
        reg_binary["00111"]="$a3";
        reg_binary["01000"]="$t0";
        reg_binary["01001"]="$t1";
        reg_binary["01010"]="$t2";
        reg_binary["01011"]="$t3";
        reg_binary["01100"]="$t4";
        reg_binary["01101"]="$t5";
        reg_binary["01110"]="$t6";
        reg_binary["01111"]="$t7";
        reg_binary["10000"]="$s0";
        reg_binary["10001"]="$s1";
        reg_binary["10010"]="$s2";
        reg_binary["10011"]="$s3";
        reg_binary["10100"]="$s4";
        reg_binary["10101"]="$s5";
        reg_binary["10110"]="$s6";
        reg_binary["10111"]="$s7";
        reg_binary["11000"]="$t8";
        reg_binary["11001"]="$t9";
        reg_binary["11010"]="$k0";
        reg_binary["11011"]="$k1";
        reg_binary["11100"]="$gp";
        reg_binary["11101"]="$sp";
        reg_binary["11110"]="$fp";
        reg_binary["11111"]="$ra";
        map<string,string>::iterator it;
        for(it=reg_binary.begin();it!=reg_binary.end();it++)
            reg[it->second]=it->first;
        labels.clear();
        label_id = 1;
    }
    string to_string(int x){//数字转字符串
        if(x==0) return "0";
        int x1=0,len=0,flag=0;
        if(x<0)x=-x,flag=1;
        while(x){
            x1=x1*10+x%10;
            len++;
            x/=10;
        }
        string num(len,'0');
        for(int i=0;i<len;i++){
            num[i]=x1%10+'0';
            x1/=10;
        }
        if(flag)num="-"+num;
        return num;
    }
    string binary2hex(string binary){//二进制转十六进制
        string hex(8,'0');
        for(int i=0;i<32;i+=4){
            int x=8*(binary[i]-'0')+4*(binary[i+1]-'0')+2*(binary[i+2]-'0')+1*(binary[i+3]-'0');
            if(x<=9)hex[i/4]=x+'0';
            else hex[i/4]='A'+x-10;
        }
        return hex;
    }
    string hex2binary(string hex){//十六进制转二进制
        string binary(32,0);
        for(int i=0;i<8;i++){
            int tmp;
            if(hex[i]>='0'&&hex[i]<='9')tmp=hex[i]-'0';
            else if(hex[i]>='a'&&hex[i]<='f')tmp=hex[i]-'a';
            else tmp=hex[i]-'A';
            if(tmp>=8)binary[i*4]='1',tmp-=8;
            if(tmp>=4)binary[i*4+1]='1',tmp-=4;
            if(tmp>=2)binary[i*4+2]='1',tmp-=2;
            if(tmp>=1)binary[i*4+3]='1',tmp-=1;
        }
        for(int i=0; i < 32; i++){
            if(binary[i] == 0){
                binary[i] = '0';
            }
        }
        return binary;
    }
    void clear(){
        label_id = 0;
        instruct.clear();
        instruct_binary.clear();
        instruct_hex.clear();
        labels.clear();
    }
    void read(int type,vector<string>machine_code){
        clear();
        if(type==0){
            instruct_binary=machine_code;
            for(int i=0;i<(int)instruct_binary.size();i++)
                instruct_hex.push_back(binary2hex(instruct_binary[i]));
        }else{
            instruct_hex=machine_code;
            for(int i=0;i<(int)instruct_hex.size();i++)
                instruct_binary.push_back(hex2binary(instruct_hex[i]));
        }
    }
    string generate_label(int target)
    {
        string label;
        auto found = labels.find(target);
        if(found == labels.end())
        {
            label = "label" + to_string(label_id++);
            labels.insert(pair<int, string>(target, label));
        }
        else label = found->second;
        return label;
    }
    bool Judge(string str){
        return (int)str.size()!=32;
    }
    void PrintError(int line){
        clear();
        cout << "Machine code error at line " << line;
    }
    int solve(int main = 0){
        labels.insert(pair<int, string>(main, "main"));
        for(int i=0;i<(int)instruct_binary.size();i++){
            string str=instruct_binary[i];
            if(Judge(str)){
                PrintError(i);
                return -i;
            }
            string op=str.substr(0,6);
            string res="";
            if(op=="000000"){//and or xor nor sll srl add sub slt jr
                int typ=Binary_change.Binary2Int(str.substr(26,6),0);
                if(typ==8){
                    //					jr rs	000000	rs	00000	00000	00000	001000 8
                    res="jr ";
                    res.append(reg_binary[str.substr(6,5)]);
                }else
                    if(typ==0||typ==2){
                        //					sll rd,rt,sa	000000	00000	rt	rd	sa	000000 0
                        //					srl rd,rt,sa	000000	00000	rt	rd	sa	000010 2
                        switch(typ){
                        case 0: res="sll ";break;
                        case 2: res="srl ";break;
                        }
                        res=res+reg_binary[str.substr(16,5)]+",";//rd
                        res=res+reg_binary[str.substr(11,5)]+",";//rt
                        res=res+to_string(Binary_change.Binary2Int(str.substr(21,5),1)); //sa
                    }else{
                        //					and rd,rs,rt	000000	rs	rt	rd	00000	100100 36
                        //					or rd,rs,rt		000000	rs	rt	rd	00000	100101 37
                        //					xor rd,rs,rt	000000	rs	rt	rd	00000	100110 38
                        //					nor rd,rs,rt	000000	rs	rt	rd	00000	100111 39
                        //					add rd,rs,rt	000000	rs	rt	rd	00000	100000 32
                        //					sub rd,rs,rt	000000	rs	rt	rd	00000	100010 34
                        //					slt rd,rs,rt	000000	rs	rt	rd	00000	101010 42
                        switch(typ){
                        case 36: res="and ";break;
                        case 37: res="or ";break;
                        case 38: res="xor ";break;
                        case 39: res="nor ";break;
                        case 32: res="add ";break;
                        case 34: res="sub ";break;
                        case 42: res="slt ";break;
                        default: break;
                        }
                        res=res+reg_binary[str.substr(16,5)]+",";//rd
                        res=res+reg_binary[str.substr(6,5)]+",";//rs
                        res=res+reg_binary[str.substr(11,5)];//rt
                    }
            }else
                if(op=="001101"){//ori
                    //				ori rs,rt,imm	001101	rs	rt	immediate
                    res="ori ";
                    res=res+reg_binary[str.substr(11,5)]+",";//rt
                    res=res+reg_binary[str.substr(6,5)]+",";//rs
                    res=res+to_string(Binary_change.Binary2Int(str.substr(16,16),1));//imm
                }else
                    if(op=="001100"){//andi
                        //				andi rt,rs,imm	001000	rs	rt	immediate
                        res="andi ";
                        res=res+reg_binary[str.substr(11,5)]+",";//rt
                        res=res+reg_binary[str.substr(6,5)]+",";//rs
                        res=res+to_string(Binary_change.Binary2Int(str.substr(16,16),1));//imm
                    }else
                        if(op=="001110"){//xori
                            //				xori rt,rs,imm	001110	rs	rt	immediate
                            res="xori ";
                            res=res+reg_binary[str.substr(11,5)]+",";//rt
                            res=res+reg_binary[str.substr(6,5)]+",";//rs
                            res=res+to_string(Binary_change.Binary2Int(str.substr(16,16),1));//imm
                        }else
                            if(op=="001111"){//lui
                                //				lui rt,imm	001111	00000	rt	immediate
                                res="lui ";
                                res=res+reg_binary[str.substr(11,5)]+",";//rt
                                res=res+to_string(Binary_change.Binary2Int(str.substr(16,16),1));//imm
                            }else
                                if(op=="001000"){//addi
                                    //				addi rt,rs,imm	001000	rs	rt	immediate
                                    res="addi ";
                                    res=res+reg_binary[str.substr(11,5)]+",";//rt
                                    res=res+reg_binary[str.substr(6,5)]+",";//rs
                                    res=res+to_string(Binary_change.Binary2Int(str.substr(16,16),1));//imm
                                }else
                                    if(op=="001010"){//slti
                                        //				slti rt,rs	001010	rs	rt	immediate
                                        res="slti ";
                                        res=res+reg_binary[str.substr(11,5)]+",";//rt
                                        res=res+reg_binary[str.substr(6,5)]+",";//rs
                                        res=res+to_string(Binary_change.Binary2Int(str.substr(16,16),1));//imm
                                    }else
                                        if(op=="000100"){//beq
                                            //				beq rs,rt,offset	000100	rs	rt	offset
                                            res="beq ";
                                            res=res+reg_binary[str.substr(6,5)]+",";//rs
                                            res=res+reg_binary[str.substr(11,5)]+",";//rt
                                            int offset = Binary_change.Binary2Int(str.substr(16,16),1);
                                            res.append(generate_label((i + 1) * 4 + offset*4));//off
                                        }else
                                            if(op=="000010"){//j
                                                //				j target	000010	target
                                                res="j ";
                                                int target = Binary_change.Binary2Int(str.substr(6,26),1);
                                                res.append(generate_label(target*4));//tar
                                            }else
                                                if(op=="000101"){//bne
                                                    //				bne rs,rt,offset	000101	rs	rt	offset
                                                    res="bne ";
                                                    res=res+reg_binary[str.substr(6,5)]+",";//rs
                                                    res=res+reg_binary[str.substr(11,5)]+",";//rt
                                                    int offset = Binary_change.Binary2Int(str.substr(16,16),1);
                                                    res.append(generate_label((i + 1) * 4 + offset*4));//off

                                                }else
                                                    if(op=="000001"){//bgez bltz
                                                        //				bgez rs,offset	000001	rs	00001	offset
                                                        //				bltz rs,offset	000001	rs	00000	offset
                                                        if(str.substr(11,5)=="00001")res="bgez ";
                                                        else res="bltz ";
                                                        res=res+reg_binary[str.substr(6,5)]+",";//rs
                                                        int offset = Binary_change.Binary2Int(str.substr(16,16),1);
                                                        res.append(generate_label((i + 1) * 4 + offset*4));//off
                                                    }else
                                                        if(op=="000111"){//bgtz
                                                            //				bgtz rs,offset	000111	rs	00000	offset
                                                            res="bgtz ";
                                                            res=res+reg_binary[str.substr(6,5)]+",";//rs
                                                            int offset = Binary_change.Binary2Int(str.substr(16,16),1);
                                                            res.append(generate_label((i + 1) * 4 + offset*4));//off
                                                        }else
                                                            if(op=="000110"){//blez
                                                                //				blez rs,offset	000110	rs	00000	offset
                                                                res="blez ";
                                                                res=res+reg_binary[str.substr(6,5)]+",";//rs
                                                                int offset = Binary_change.Binary2Int(str.substr(16,16),1);
                                                                res.append(generate_label((i + 1) * 4 + offset*4));//off
                                                            }else
                                                                if(op=="000011"){//jal
                                                                    //				jal target	000011	target
                                                                    res="jal ";
                                                                    int target = Binary_change.Binary2Int(str.substr(6,26),1);
                                                                    res.append(generate_label(target*4));//tar
                                                                }else
                                                                    if(op=="100011"){//lw
                                                                        //				lw rt,offset(rs)	100011	rs	rt	offset
                                                                        res="lw ";
                                                                        res=res+reg_binary[str.substr(11,5)]+",";//rt
                                                                        res=res+to_string(Binary_change.Binary2Int(str.substr(16,16),1))+"(";//off
                                                                        res=res+reg_binary[str.substr(6,5)]+")";//rs

                                                                    }else
                                                                        if(op=="101011"){//sw
                                                                            //				sw rt,offset(rs)	101011	rs	rt	offset
                                                                            res="sw ";
                                                                            res=res+reg_binary[str.substr(11,5)]+",";//rt
                                                                            res=res+to_string(Binary_change.Binary2Int(str.substr(16,16),1))+"(";//off
                                                                            res=res+reg_binary[str.substr(6,5)]+")";//rs
                                                                        }
            if(res==""){
                PrintError(i);
                return -i;
            }
            instruct.push_back(res);
        }
        for(auto &address : labels)
        {
            instruct[address.first / 4] = address.second + ": " + instruct[address.first / 4];
        }
        return 0;
    }
    void Print(){
        for(int i=0;i<(int)instruct.size();i++)
            cout<<instruct[i]<<endl;
    }
}disassembly;

/**
 * 汇编器
 * 成员变量： instructions    汇编代码
 *          machine_code    2进制机器码
 *          machine_code_H  16进制机器码
 *          command         指令集
 *          labels          标签集
 * 成员函数： void clear()                         清空机器码、标签集
 *          void read(vector<string>)            读入汇编代码
 *          string trim(string)                  去除首尾空格
 *          int solve()                          汇编代码转换为机器码，返回main标签所在代码行，机器码存储在machine_code
 *          void print_machine_code(int)         radix == 2 打印2进制机器码， radix == 16 打印16进制机器码
 *          void code_B2code_H()                 2进制机器码转16进制机器码
 *          void print_source_code()             打印汇编代码(规范化后)
 * 注：
 *  solve()返回值如果为非负数，则为main函数地址
 *  solve()返回值为负数，则是汇编语法等出错的所在行数
 */
class ASSEMBLER
{
public:
    vector<string> instructions;
    vector<string> machine_code;
    vector<string> machine_code_H;
    map<string, string> command;
    map<string, int> labels;

    ASSEMBLER()
    {
        instructions.clear();
        machine_code.clear();
        labels.clear();
        // 命令集
        command["and" ] = "000000100100"; // 12
        command["or"  ] = "000000100101";
        command["xor" ] = "000000100110";
        command["nor" ] = "000000100111";
        command["add" ] = "000000100000";
        command["sub" ] = "000000100010";
        command["slt" ] = "000000101010";
        command["jr"  ] = "000000001000";
        command["sll" ] = "000000000000";
        command["srl" ] = "000000000010";
        command["bgez"] = "00000100001"; // 11
        command["bltz"] = "00000100000";
        command["bgtz"] = "00011100000";
        command["blez"] = "00011000000";
        command["ori" ] = "001101"; // 6
        command["andi"] = "001100";
        command["xori"] = "001110";
        command["lui" ] = "001111";
        command["addi"] = "001000";
        command["slti"] = "001010";
        command["beq" ] = "000100";
        command["j"   ] = "000010";
        command["bne" ] = "000101";
        command["jal" ] = "000011";
        command["lw"  ] = "100011";
        command["sw"  ] = "101011";
    }

    void clear()
    {
        machine_code.clear();
        labels.clear();
    }

    //    string adjust(string instr) // 汇编代码规范化
    //    {
    //        string adjust_instr("");
    //
    //        int label_def = instr.find(":");
    //        if(label_def != instr.npos) // 提取label标签
    //        {
    //            string label = instr.substr(0, label_def);
    //            int label_begin = label.find_first_not_of(' ');
    //            int label_end = label.find_last_not_of(' ');
    //            label = label.substr(label_begin, label_end - label_begin + 1);
    //            adjust_instr = label + ": ";
    //            instr = instr.substr(label_def + 1);
    //        }
    //
    //        stringstream sstream(instr);
    //
    //        string operation;
    //        if(sstream >> operation) // 提取操作码
    //        {
    //            adjust_instr.append(operation + " ");
    //            char ch;    // 获取后续内容 寄存器、立即数等
    //            while(sstream >> ch)    // 剔除空格
    //                if(ch != ' ' && ch != '\t') adjust_instr.push_back(ch);
    //        }
    //
    //        return adjust_instr;
    //    }

    void read(vector<string> instrs) // 读入汇编代码
    {
        instructions.clear();
        instructions = instrs;
    }

    //    void read() // 由控制台读入汇编代码
    //    {
    //        instructions.clear();
    //        do
    //        {
    //            string instruction;
    //            getline(cin, instruction);
    //            if(instruction == "") continue;
    //            instructions.push_back(instruction);
    //        } while(!cin.eof());
    //    }

    string trim(string str)
    {
        if(str.empty()) return "";
        int first_not_space = str.find_first_not_of(' ');
        int last_not_space = str.find_last_not_of(' ');
        return str.substr(first_not_space, last_not_space - first_not_space + 1);
    }

    int solve()
    {
        clear();
        {
            stack<string> labelstack;
            regex pattern("(\\s*[a-zA-Z_][a-zA-Z0-9_]*\\s*:\\s*|\\s*)(.*)?"); // 匹配“标签:指令”
            smatch result;
            for (int line = 0, i = 0; i < instructions.size(); ++i) // 查找label标签,计入map
            {
                if(regex_match(instructions[i], result, pattern)) // 标签: result[1] ; 指令 result[2]
                {
//                    if(!trim(result[1].str()).empty()) // 有标签
//                    {
//                        labelstack.push(result[1].str());
//                    }
                    string Labelstr = trim(result[1].str());
                    if(!Labelstr.empty()) // 有标签
                    {
                        Labelstr = trim(Labelstr.substr(0, Labelstr.size() - 1));
                        labelstack.push(Labelstr);
                    }
                    string instr = trim(result[2].str());
                    if(!instr.empty()) // 不是唯标签指令
                    {
                        while(!labelstack.empty())
                        {
                            string label = labelstack.top();
                            labels.insert(pair<string, int>(label, line * 4));
                            labelstack.pop();
                        }
                        line += 1;
                    }
                    instructions[i] = instr;
                }
                else return -i;
            }
        }

        regex pattern("([a-zA-Z]+)\\s+(.*)"); // 操作指令 操作数
        regex RItype("([$a-z0-9]+)\\s*,\\s*([$a-z0-9]+)\\s*,\\s*(-?[$a-zA-Z0-9_]+).*"); // 寄存器,寄存器,寄存器或立即数 注释
        regex Jtype("([$a-zA-Z0-9_]+).*"); // 寄存器或16进制地址 注释
        regex Load_Save("([$a-z0-9]+)\\s*,\\s*(-?\\d+)\\s*\\(\\s*([$a-z0-9]+)\\s*\\).*"); // 寄存器,立即数(寄存器) 注释
        regex Pseudo("([$a-z0-9]+)\\s*,\\s*(-?[a-zA-Z0-9_]+).*");
        smatch result;
        for(int line = 0, i = 0;i < instructions.size();++i) // 汇编代码转为机器码
        {
            if(instructions[i].empty()) continue;

            string res(""), opcode, operands;

            if(regex_match(instructions[i], result, pattern))
            {
                opcode = result[1].str();
                operands = result[2].str();
            }
            else return -i;

            if(command.find(opcode) == command.end()) return -i; // command not exist

            if
                (
                    opcode == "and" || opcode == "or" || opcode == "xor" ||
                    opcode == "nor" || opcode == "add"|| opcode == "sub" ||
                    opcode == "slt"
                    ) // R型指令
            {
                string rs, rt, rd;
                if(regex_match(operands, result, RItype))
                {
                    rd = result[1].str();
                    rs = result[2].str();
                    rt = result[3].str();
                }
                else return -i;
                if(disassembly.reg.find(rs) == disassembly.reg.end() ||
                    disassembly.reg.find(rt) == disassembly.reg.end() ||
                    disassembly.reg.find(rd) == disassembly.reg.end()
                    ) return -i; // register not exist
                res.append(command[opcode].substr(0, 6)); // opcode
                res.append(disassembly.reg[rs]); // rs
                res.append(disassembly.reg[rt]); // rt
                res.append(disassembly.reg[rd]); // rd
                res.append("00000"); // shamt
                res.append(command[opcode].substr(6, 6)); // opcode
            }
            else if
                (
                    opcode == "sll" || opcode == "srl"
                    ) // I 型指令
            {
                string rt, rd; int sa;
                if(regex_match(operands, result, RItype))
                {
                    rd = result[1].str();
                    rt = result[2].str();
                    try{
                        sa = stoi(result[3].str());
                    } catch(const std::invalid_argument& e){
                        return -i;
                    }
                }
                else return -i;
                if(disassembly.reg.find(rd) == disassembly.reg.end() ||
                    disassembly.reg.find(rt) == disassembly.reg.end() ||
                    (sa > 31 || sa < 0)
                    ) return -i; // register not exist or overflow
                res.append(command[opcode].substr(0, 6)); // opcode
                res.append("00000"); // none
                res.append(disassembly.reg[rt]); // rt
                res.append(disassembly.reg[rd]); // rd
                res.append(Binary_change.Int2Binary_unsigned(sa, 5)); // sa
                res.append(command[opcode].substr(6, 6)); // opcode
            }
            else if
                (
                    opcode == "jr"
                    ) // R型指令
            {
                string rs;
                if(regex_match(operands, result, Jtype))
                {
                    rs = result[1].str();
                }
                else return -i;
                if(disassembly.reg.find(rs) == disassembly.reg.end()
                    ) return -i; // register not exist
                res.append(command[opcode].substr(0, 6));
                res.append(disassembly.reg[rs]);
                res.append("00000");
                res.append("00000");
                res.append("00000");
                res.append(command[opcode].substr(6, 6));
            }
            else if
                (
                    opcode == "ori" || opcode == "andi" || opcode == "xori" ||
                    opcode == "addi"|| opcode == "slti"
                    ) // I 型指令
            {
                string rs, rt; int imm;
                if(regex_match(operands, result, RItype))
                {
                    rt = result[1].str();
                    rs = result[2].str();
                    try{
                        imm = stoi(result[3].str());
                    } catch(const std::invalid_argument& e){
                        return -i;
                    }
                }
                else return -i;
                if(disassembly.reg.find(rs) == disassembly.reg.end() ||
                    disassembly.reg.find(rt) == disassembly.reg.end() ||
                    (imm > (1<<15) - 1 || imm < -(1<<15))
                    ) return -i; // register not exist or overflow
                res.append(command[opcode]);
                res.append(disassembly.reg[rs]);
                res.append(disassembly.reg[rt]);
                res.append(Binary_change.Int2Complement(imm, 16));
            }
            else if
                (
                    opcode == "lui"
                    ) // I 型指令
            {
                string rt; int imm;
                if(regex_match(operands, result, Pseudo))
                {
                    rt = result[1].str();
                    try{
                        imm = stoi(result[2].str());
                    } catch(const std::invalid_argument& e){
                        return -i;
                    }
                }
                else return -i;
                if(disassembly.reg.find(rt) == disassembly.reg.end() ||
                    (imm > (1<<15) - 1 || imm < -(1<<15))
                    ) return -i; // register not exist or overflow
                res.append(command[opcode]);
                res.append("00000");
                res.append(disassembly.reg[rt]);
                res.append(Binary_change.Int2Complement(imm, 16));
            }
            else if
                (
                    opcode == "beq" || opcode == "bne"
                    ) // I 型指令
            {
                string rs, rt, label;
                if(regex_match(operands, result, RItype))
                {
                    rs = result[1].str();
                    rt = result[2].str();
                    label = result[3].str();
                }
                else return -i;
                if(disassembly.reg.find(rs) == disassembly.reg.end() ||
                    disassembly.reg.find(rt) == disassembly.reg.end() ||
                    labels.find(label) == labels.end()
                    ) return -i; // register or label not exist
                res.append(command[opcode]);
                res.append(disassembly.reg[rs]);
                res.append(disassembly.reg[rt]);
                res.append(Binary_change.Int2Complement(labels[label] / 4 - (line + 1), 16));
            }
            else if
                (
                    opcode == "bgez" || opcode == "bltz" || opcode == "bgtz" ||
                    opcode == "blez"
                    )
            {
                string rs, label;
                if(regex_match(operands, result, Pseudo))
                {
                    rs = result[1].str();
                    label = result[2].str();
                }
                else return -i;
                if(disassembly.reg.find(rs) == disassembly.reg.end() ||
                    labels.find(label) == labels.end()
                    ) return -i; // register or label not exist
                res.append(command[opcode].substr(0, 6));
                res.append(disassembly.reg[rs]);
                res.append(command[opcode].substr(6, 5));
                res.append(Binary_change.Int2Complement(labels[label] / 4 - (line + 1), 16));
            }
            else if
                (
                    opcode == "j" || opcode == "jal"
                    ) // J 型指令
            {
                string label;
                if(regex_match(operands, result, Jtype))
                {
                    label = result[1].str();
                }
                else return -i;
                if(labels.find(label) == labels.end()
                    ) return -i; // register not exist
                res.append(command[opcode]);
                res.append(Binary_change.Int2Binary_unsigned(labels[label] / 4, 26));
            }
            else if
                (
                    opcode == "lw" || opcode == "sw"
                    ) // I 型指令
            {
                string rs, rt; int imm;
                if(regex_match(operands, result, Load_Save))
                {
                    rt = result[1].str();
                    try{
                        imm = stoi(result[2].str());
                    } catch(const std::invalid_argument& e){
                        return -i;
                    }
                    rs = result[3].str();
                }
                else return -i;
                if(disassembly.reg.find(rs) == disassembly.reg.end() ||
                    disassembly.reg.find(rt) == disassembly.reg.end() ||
                    (imm > (1<<15) - 1 || imm < -(1<<15))
                    ) return -i; // register not exist or overflow
                res.append(command[opcode]);
                res.append(disassembly.reg[rs]);
                res.append(disassembly.reg[rt]);
                res.append(Binary_change.Int2Complement(imm, 16));
            }

            machine_code.push_back(res);
            line += 1;
        }

        if(labels.count("main") == 0) return 0;
        return labels["main"];
    }

    void code_B2code_H() // 2进制机器码转16进制
    {
        for(string instr : machine_code)
        {
            machine_code_H.push_back(disassembly.binary2hex(instr));
        }
    }

    void print_source_code() // 打印源代码
    {
        for(string instr : instructions)
            cout << instr << endl;
    }

    void print_machine_code(int radix = 2) // 打印机器码
    {
        if(radix == 2)
            for(string instr : machine_code)
                cout << instr << endl;
        else if(radix == 16)
            for(string instr : machine_code_H)
                cout << instr << endl;
    }
} assembler; // 定义一个汇编器的全局变量

typedef unsigned int REGISTER;

/**
 * Mips模拟器定义如下
 * PC为指令计数器
 * reg[]为所有32个寄存器
 * memo[]代表内存，但是实际上栈空间也包含在内(初始值40000)
 * 将机器码，main函数的地址作为参数输入load_and_execute()即可
 * 单步调试，请先将机器码，main函数地址传入load(),再使用execute()即可
 */
class MIPS
{
public:
    unsigned int PC;
    REGISTER reg[32];
    REGISTER memo[65536];
    bool debug[65536];
    vector<string> machine_code;

    MIPS(): PC(0) {
        for(int i = 0;i < 31;++i) reg[i] = 0;
        reg[29] = (unsigned int)40000; // 初始化$sp
    }

    void initial(){
        for(int i = 0;i < 31;++i) reg[i] = 0;
        reg[29] = (unsigned int)40000; // 初始化$sp
    }

    void load(vector<string> maccode, int main = 0)
    {
        PC = main;
        machine_code = maccode;
    }

    unsigned int execute()
    {
//        if(debug[PC] == true){
//            return PC;
//        }
        if(PC >= machine_code.size() * 4) return false; // 运行完成
        int row = PC / 4;
        PC += 4;
        string op = machine_code[row].substr(0, 6);
        if(op == "000010") // j
        {
            int target = Binary_change.Binary2Int(machine_code[row].substr(6, 26), 0);
            PC = PC & 0xf0000000 | (target << 2) & 0x0fffffff;
        }
        else if (op == "000011") // jal
        {
            int target = Binary_change.Binary2Int(machine_code[row].substr(6, 26), 0);
            reg[31] = PC; /* $ra = PC */
            PC = PC & 0xf0000000 | (target << 2) & 0x0fffffff;
        }
        else if(op == "000000") // R 型指令
        {
            int function = Binary_change.Binary2Int(machine_code[row].substr(26, 6), 0);
            int rs = Binary_change.Binary2Int(machine_code[row].substr(6, 5), 0);
            int rt = Binary_change.Binary2Int(machine_code[row].substr(11, 5), 0);
            int rd = Binary_change.Binary2Int(machine_code[row].substr(16, 5), 0);
            int shamt = Binary_change.Binary2Int(machine_code[row].substr(21, 5), 1);
            switch(function)
            {
            case 0	/* sll */:
                reg[rd] = reg[rt] << shamt;
                break;
            case 2 	/* srl */:
                reg[rd] = reg[rt] >> shamt;
                break;
            case 8 	/* jr  */:
                PC = reg[rs];
                break;
            case 32 /* add */:
                reg[rd] = (int)reg[rs] + (int)reg[rt];
                break;
            case 34 /* sub */:
                reg[rd] = (int)reg[rs] - (int)reg[rt];
                break;
            case 36 /* and */:
                reg[rd] = reg[rs] & reg[rt];
                break;
            case 37 /* or  */:
                reg[rd] = reg[rs] | reg[rt];
                break;
            case 38 /* xor */:
                reg[rd] = reg[rs] ^ reg[rt];
                break;
            case 39 /* nor */:
                reg[rd] = ~(reg[rs] | reg[rt]);
                break;
            case 42 /* slt */:
                reg[rd] = (int)reg[rs] < (int)reg[rt];
                break;
            }
        }
        else
        {
            int operation = Binary_change.Binary2Int(op, 0);
            int rs = Binary_change.Binary2Int(machine_code[row].substr(6, 5), 0);
            int rt = Binary_change.Binary2Int(machine_code[row].substr(11, 5), 0);
            int imm = Binary_change.Binary2Int(machine_code[row].substr(16, 16), 1);
            switch(operation)
            {
            case 1	/* bgez || bltz */:
                if(rt == 1 && (int)reg[rs] >= (int)reg[0]) PC += imm << 2;
                else if(rt == 0 && (int)reg[rs] < (int)reg[0]) PC += imm << 2;
                break;
            case 4 	/* beq */:
                if((int)reg[rs] == (int)reg[rt]) PC += imm << 2;
                break;
            case 5	/* bne */:
                if((int)reg[rs] != (int)reg[rt]) PC += imm << 2;
                break;
            case 6 	/* blez */:
                if((int)reg[rs] <= (int)reg[0]) PC += imm << 2;
                break;
            case 7 	/* bgtz */:
                if((int)reg[rs] > (int)reg[0]) PC += imm << 2;
                break;
            case 8  /* addi */:
                reg[rt] = (int)reg[rs] + imm;
                break;
            case 10 /* slti */:
                reg[rt] = (int)reg[rs] < imm;
                break;
            case 12 /* andi */:
                reg[rt] = reg[rs] & imm;
                break;
            case 13 /* ori */:
                reg[rt] = reg[rs] | imm;
                break;
            case 14 /* xori */:
                reg[rt] = reg[rs] ^ imm;
                break;
            case 15 /* lui */:
                reg[rt] = (unsigned int)(imm) << 16;
                break;
            case 35	/* lw */:
                reg[rt] = memo[((int)reg[rs] + imm) / 4];
                break;
            case 43 /* sw */:
                memo[((int)reg[rs] + imm) / 4] = reg[rt];
                break;
            }
        }
        reg[0] = 0; // $zero can't be changed
        return true;
    }

    void write(vector<string> maccode, int main = 0){
        int i = 0;
        for(auto &item: maccode){
            memo[i] = stoul(item, 0 ,2);
            i++;
        }
    }

    void load_and_execute(vector<string> maccode, int main = 0) // 机器码
    {
        initial();
        load(maccode, main);
        while(execute());
        write(maccode, main);
    }
} mips;


int main()
{
    // 测试  汇编与反汇编  流程： 读入汇编代码->汇编->反汇编->汇编
    //    assembler.read(); cout << endl;
    //    cout << endl; assembler.print_source_code();
    //
    //    cout << assembler.solve();
    //    cout << endl; assembler.print_machine_code();

    //    disassembly.instruct_binary = assembler.machine_code;
    //
    //    disassembly.solve();
    //    cout << endl; disassembly.Print();
    //
    //    assembler.instructions = disassembly.instruct;
    //
    //    assembler.solve();
    //    cout << endl; assembler.print_machine_code();

    // 测试  模拟运行    流程： 读入汇编代码->汇编->模拟运行
    //    assembler.read(); cout << endl;
    //    cout << endl; assembler.print_source_code();
    //    int main = assembler.solve();
    //    cout << endl; assembler.print_machine_code();
    //
    //    mips.load_and_execute(assembler.machine_code, main);
    //    // 随便设置的检查
    //    cout << endl << mips.reg[8]; // $t0

    return 0;
}
