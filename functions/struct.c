#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include "../handlers/winProc.h"
#include "../handlers/clientes.h"
#include "../handlers/struct.h"
#include "../handlers/caracteres.h"

void delete_table_row_client(char* ID)
{
        int row = search_clients(ID);

        delete_client(row);

        DestroyWindow(hBodyClientes);
}

void SortDateStructClient(STRUCTCLIENTESDATA *data, int type, int len)
{
        if (type == 0)
        {
                for (int i = 1; i < len; i++)
                {
                        for (int z = 0; z < len - i; z++)
                        {
                                char date1[16];
                                char date2[16];

                                strcpy(date1, data[z].date);
                                strcpy(date2, data[z + 1].date);

                                char mounth1[5];
                                char mounth2[5];

                                substr(mounth1, date1, 3, 5);
                                substr(mounth2, date2, 3, 5);

                                char day1[5];
                                char day2[5];

                                substr(day1, date1, 0, 2);
                                substr(day2, date2, 0, 2);

                                char year1[8];
                                char year2[8];

                                substr(year1, date1, 6, 10);
                                substr(year2, date2, 6, 10);

                                if (atoi(year1) < atoi(year2))
                                        continue;
                                else if (atoi(year1) > atoi(year2))
                                {
                                        STRUCTCLIENTESDATA temp;
                                        temp = data[z];
                                        data[z] = data[z + 1];
                                        data[z + 1] = temp;
                                        continue;
                                }
                                else if (atoi(mounth1) > atoi(mounth2))
                                {
                                        STRUCTCLIENTESDATA temp;
                                        temp = data[z];
                                        data[z] = data[z + 1];
                                        data[z + 1] = temp;
                                        continue;
                                }
                                else if (atoi(day1) > atoi(day2))
                                {
                                        STRUCTCLIENTESDATA temp;
                                        temp = data[z];
                                        data[z] = data[z + 1];
                                        data[z + 1] = temp;
                                }
                        }
                }
        }
        else if (type == 1)
        {
                for (int i = 1; i < len; i++)
        {
                for (int z = 0; z < len - i; z++)
                {
                        char date1[12];
                        char date2[12];

                        strcpy(date1, data[z].date);
                        strcpy(date2, data[z + 1].date);

                        char mounth1[5];
                        char mounth2[5];

                        substr(mounth1, date1, 3, 5);
                        substr(mounth2, date2, 3, 5);

                        char day1[5];
                        char day2[5];

                        substr(day1, date1, 0, 2);
                        substr(day2, date2, 0, 2);

                        char year1[5];
                        char year2[5];

                        substr(year1, date1, 6, 10);
                        substr(year2, date2, 6, 10);

                        if (atoi(year1) > atoi(year2))
                                continue;
                        else if (atoi(year1) < atoi(year2))
                        {
                                STRUCTCLIENTESDATA temp;
                                temp = data[z];
                                data[z] = data[z + 1];
                                data[z + 1] = temp;
                                continue;
                        }
                        else if (atoi(mounth1) < atoi(mounth2))
                        {
                                STRUCTCLIENTESDATA temp;
                                temp = data[z];
                                data[z] = data[z + 1];
                                data[z + 1] = temp;
                                continue;
                        }
                        else if (atoi(day1) < atoi(day2))
                        {
                                STRUCTCLIENTESDATA temp;
                                temp = data[z];
                                data[z] = data[z + 1];
                                data[z + 1] = temp;
                        }
                }
        }
        }
}

void SetWindowPosition(WINDOWPOS* pos, int x, int y, int cx, int cy){
        pos->x = x;
        pos->y = y;
        pos->cx = cx;
        pos->cy = cy;
}