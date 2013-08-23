/*******************************
问题描述：
将输入的字符串（字符串仅包含小写字母‘a’到‘z
’），按照如下规则，循环转换后输出：a->b,b->c,…,y->z,z->a
；若输入的字符串连续出现两个字母相同时，后一个字母需要连续转换2次。例如：aa 
转换为 bc，zz 转换为 ab
；当连续相同字母超过两个时，第三个出现的字母按第一次出现算。
要求实现函数：
void convert(char *input,char* output)
【输入】  char *input , 输入的字符串
【输出】  char *output ，输出的字符串
【返回】 无
示例
输入：char*input="abcd" 
输出：char*output="bcde"
输入：char*input="abbbcd" 
输出：char*output="bcdcde"

*******************************/

#include <stdio.h>
#include <string.h>

void convert(char *input, char *output)
{
    int contin;
    int i;

    for(i = 0, contin = 1; i < strlen(input); ++i) 
    {
        if (contin == 2)
            contin = 1;
        else if (i - 1 >= 0 && input[i-1] == input[i])
            contin++;
        output[i] = (char)(input[i]+contin);
     }
}

int main(void)
{
    char *input1="abcd";
    char output1[5];
    char *input2="bbbbbb";
    char output2[7];

    convert(input1, output1);
    convert(input2, output2);
    printf("input: %s\n output: %s\n\n", input1, output1);
    printf("input: %s\n output: %s\n\n", input2, output2);
    return 0;
}

