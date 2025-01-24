#include <iostream>
#include <stdio.h>
enum  Token_Type {
    EOF_TOKEN = 0,  //规定文件的结束
    NUMERIC_TOKEN,  //当前token是数值类型的
    IDENTIFIER_TOKEN,   //当前token是标识符
    PARAN_TOKEN,    //当前token是括号
    DEF_TOKEN   //当前token是def声明，之后的函数定义
};
FILE *file;
//持有数值 存储当前解析到的数值
static int Numberic_Val;
//持有标识符字符串名字
static std::string Identifer_string;
static int get_token(){
    static int LastChar = ' ';
    //这段代码用来跳过文件中的空白字符
    //检查 LastChar 是否为空白字符（如空格、换行符等
    while (isspace(LastChar)) {
        //从文件中读取一个字符，并更新 LastChar
        LastChar = fgetc(file);
    } 
    // 检测LastChar是否为字母
    if (isalpha(LastChar)){
        Identifer_string = LastChar;
        while(isalnum((LastChar = fgetc(file)))){
            Identifer_string +=LastChar;
        }
        if((Identifer_string == "def")){
            return DEF_TOKEN;
        }
        return IDENTIFIER_TOKEN;
    }
    if (isdigit(LastChar)){
        std::string NumStr;
        do{
            NumStr += LastChar;
            LastChar = fgetc(file);
        }while(isdigit(LastChar));
        Numberic_Val = strtod(NumStr.c_str(),0);
        return NUMERIC_TOKEN;
    }
    if (LastChar == '#'){
        do{
            LastChar = fgetc(file);
        }while(LastChar != EOF && LastChar != '\n' && LastChar !='\r');
        if (LastChar !=EOF)
        {
            return get_token();
        }
        
    }
    if (LastChar == EOF){
        return EOF_TOKEN;
    }

    int ThisChar = LastChar;
    LastChar = fgetc(file);
    return ThisChar;
}