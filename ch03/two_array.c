int pointer_two_array(){
    int array[3][4] = { {1, 2, 3, 4} , {5, 6, 7, 8}, {9, 10, 11, 12}};
    int n = sizeof(array)/sizeof(array[0]);         // число строк
    int m = sizeof(array[0])/sizeof(array[0][0]);   // число столбцов

    int *final = array[0] + n * m - 1;  // указатель на самый последний элемент
    for(int *ptr=array[0], i = 1; ptr <= final; ptr++, i++)
    {
        printf("%d \t", *ptr);
        // если остаток от целочисленного деления равен 0,
        // переходим на новую строку
        if(i%m==0)
        {
            printf("\n");
        }
    }

int pointer_two_array_(){
     int M[2][2] = { {1, 2} , {3, 4} };

        // (*mp)[k] => (*mp)[k] => mp[0][k].
        int (*mp)[2] = M; //again you must not add '&' to variable M.
        printf("M[0][0] = %d\n", **mp);//get array and extract it first element
        printf("M[1][0] = %d\n", **(mp + 1));//move to the address of second element
        printf("M[1][1] = %d\n", *( *(mp + 1) + 1));

    return 0;
    }
}

void charArr()
{
     char mas[6][8] = {

        {'#', '#', '#', '#', '#', '#', '#','\0'},
        {'#', ' ', ' ', ' ', ' ', ' ', '#','\0'},
        {'#', ' ', ' ', ' ', ' ', ' ', '#','\0'},
        {'#', ' ', ' ', ' ', ' ', ' ', '#','\0'},
        {'#', ' ', ' ', ' ', ' ', ' ', '#','\0'},
        {'#', ' ', ' ', ' ', ' ', ' ', '#','\0'},
        };

        int n = sizeof(mas)/sizeof(mas[0]);         // число строк
        int m = sizeof(mas[0])/sizeof(mas[0][0]);   // число столбцов

        // проходим по 6 строкам таблицы
        for (int i = 0; i < n; ++i)
        {
            // проходим по 7 строкам таблицы
            for (int j = 0; j < m; ++j)
            {
                printf("%c ", mas[i][j]);
            }
            printf( "\n" );

        }

}



void num()
{
    int num[6][7] = {

        { 1 , 1 , 1 , 1 , 1 , 1 , 1 },
        { 1 , 0 , 0 , 0 , 0 , 0 , 1 },
        { 1 , 0 , 0 , 0 , 0 , 0 , 1 },
        { 1 , 0 , 0 , 0 , 0 , 0 , 1 },
        { 1 , 0 , 0 , 0 , 0 , 0 , 1 },
        { 1 , 0 , 0 , 0 , 0 , 0 , 1 },
        };

    // проходим по 6 строкам таблицы
    for (int i = 0; i < 6; ++i)
    {
        // проходим по 7 строкам таблицы
        for (int j = 0; j < 8; ++j)
        {
            printf("%d ", num[i][j]);
        }
        printf( "\n" );

    }


}

