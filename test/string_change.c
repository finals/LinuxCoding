/*******************************
����������
��������ַ������ַ���������Сд��ĸ��a������z
�������������¹���ѭ��ת���������a->b,b->c,��,y->z,z->a
����������ַ�����������������ĸ��ͬʱ����һ����ĸ��Ҫ����ת��2�Ρ����磺aa 
ת��Ϊ bc��zz ת��Ϊ ab
����������ͬ��ĸ��������ʱ�����������ֵ���ĸ����һ�γ����㡣
Ҫ��ʵ�ֺ�����
void convert(char *input,char* output)
�����롿  char *input , ������ַ���
�������  char *output ��������ַ���
�����ء� ��
ʾ��
���룺char*input="abcd" 
�����char*output="bcde"
���룺char*input="abbbcd" 
�����char*output="bcdcde"

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

