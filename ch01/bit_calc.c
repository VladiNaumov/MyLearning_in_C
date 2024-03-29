#include <stdio.h>


void int_to_binary( int x, char* in_str)
{
    char str_tmp[9] = {};
    unsigned char i, j, k;
    unsigned char bt[4] = {0};

    for (j=0; j<4; j++)
    {
        if(((x >> j*8)==0) && (j>0))	break;
        bt[j] = (unsigned char) (x >> j*8);

    }

    strcpy(in_str,"0b");

    for (k=0; k<j; k++)
    {
         for (i=0; i<8; i++)
        {

            switch ((bt[j-k-1] >> i) & 0b00000001)
            {
                case 1:  str_tmp[7-i] = '1'; break;
                case 0:  str_tmp[7-i] = '0'; break;
            }
        }

    }

    strcat(in_str,str_tmp);

}


int main()
{
    char str1[35] = {};
    unsigned char a=0b10101010, b=0b10001001;
    unsigned char res;

/*
    Произведём операцию & между значениями наших переменных
*/
    res = a & b;
    int_to_binary(a, str1);
    printf("%s\n", str1);
    printf("    &\n");
    int_to_binary(b, str1);
    printf("%s\n", str1);
    printf("-----------\n");
    int_to_binary(res, str1);
    printf("%s\n", str1);
    printf("\n");

    

    /*
    применением операции ИЛИ
    */ 
	res = a | b;
    int_to_binary(a, str1);
    printf("%s\n", str1);
    printf("    |\n");
    int_to_binary(b, str1);
    printf("%s\n", str1);
    printf("-----------\n");
    int_to_binary(res, str1);
    printf("%s\n", str1);
    printf("\n");



    /*
        операция Исключающее ИЛИ
    */

    res = a ^ b;
    int_to_binary(a, str1);
    printf("%s\n", str1);
    printf("   ^\n");
    int_to_binary(b, str1);
    printf("%s\n", str1);
    printf("-----------\n");
    int_to_binary(res, str1);
    printf("%s\n", str1);
    printf("\n");


    /*
    унарный оператор отрицания
    */
    res = ~a;
    int_to_binary(a, str1);
    printf("%s\n", 	str1);
    printf("   ~\n");
    int_to_binary(res, str1);
    printf("%s\n", str1);
    printf("\n");




   /*
        Теперь проверим работу со сдвигами. Сдвигать будем одно и то же число, но в разные стороны и на разное количество пунктов
    */
	
	int_to_binary(a, str1);
    printf("%s\n", str1);

    res = a>>2;
    printf("  a>>2\n");
    int_to_binary(res, str1);
    printf("%s\n", str1);

    res = a<<2;
    printf("  a<<2\n");
    int_to_binary(res, str1);
    printf("%s\n", str1);

    res = a>>4;
    printf("  a>>4\n");
    int_to_binary(res, str1);
    printf("%s\n", str1);

    res = a<<4;
    printf("  a<<4\n");
    int_to_binary(res, str1);
    printf("%s\n", str1);
}

/*----------------------------------------------*/

#include <stdlib.h>

#define BIT0 0
#define BIT1 1
#define BIT2 2
#define BIT3 3
#define BIT4 4
#define BIT5 5
#define BIT6 6
#define BIT7 7


int main(){


 char str1[35] = {};
 unsigned char a=0b11000011;

  //Установим два бита в числе
  int_to_binary(a, str1);
  printf("%s\n", str1);
  a |= ((1<<BIT3) | (1<<BIT4));

/*

Здесь происходит присваивание одновременно с операцией ИЛИ. 
А вообще здесь сначала мы получаем два числа, в которых все нули кроме того бита, который нам надо установить в значении переменной a. 
Такие числа получаются засчёт того, что мы единицу, являющуюся левым операндом в обоих данных операциях сдвигаем на такое количество пунктов, 
бит с номером которого мы и хотим установить. Некоторые путают, что будто мы макрос BIT3 или BIT4 сдвигаем на 1 влево. 
Кто не знаком с операциями сдвига, того может охватить вполне такой оптический обман. 
Затем результаты наших обоих операций также складываются логически при помощи операции ИЛИ 
и результатом всего выражения и будет число с установленными битами с индексами наших макросов. 
Затем происходит операция ИЛИ между значением переменной a, которое она имела до нашей операции с результатом выражения справа 
и результат данной операции присваивается опять же переменной a. Таким образом, в данной переменной установятся соответствующие биты, 
а остальные биты не изменят своего состояния.

*/

  printf("bit3 and bit4 SET\n");
  int_to_binary(a, str1);
  printf("%s\n", str1);


  unsigned char a=0b11000011;
  
  //Сбросим два бита в числе
  int_to_binary(a, str1);
   printf("%s\n", str1);
  a &= ~((1<<BIT6) | (1<<BIT1));

  /*
  
  Происходит всё аналогично. Мы сначала, так сказать, готовим для сброса битов маску. 
  Готовится число с теми установленными битами в байте, которые нам надо, наоборот, сбросить.
  Затем мы это число инвертируем с помощью операции отрицания (оператор тильда ~). 
  Затем уже инвертированное число, в котором будут все биты равны единице, за исключением тех, которые надо сбросить. 
  С данным числом и со значением переменной a мы уже производим операцию логического умножения И, 
  в результате которой сбросятся биты с такими номерами, в байтах под номером которых в левом операнде будут нули. 
  А затем результат данной операции опять присвоится переменной a.
  
  */
  printf("bit6 and bit1 RESET\n");
  int_to_binary(a, str1);
  printf("%s\n", str1);

}

 

