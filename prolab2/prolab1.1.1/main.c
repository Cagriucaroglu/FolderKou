#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>


void Guncelle(const char* dirname , char etiket[20] , char degistir[20])
{

    char txtspath[100] = {0};
    char txtadi[100] = {0};
    int i = 0;
    FILE *file;

    DIR *dir = opendir(dirname);

    //  printf("Dosyalar %s de okunuyor\n",dirname);

    struct dirent *entity;

    while ((entity = readdir(dir)) != NULL)
    {
        char temp[20];
        int txtmi = 1;
        int j = 0;
        int p=0;
        int y;
        int sonuc;
        char dsysatir[100];
        int etiketuzunluk;

        // printf("%d      %s          %s\n",entity->d_type , dirname , entity->d_name);

        if (entity->d_type < 33000 && entity->d_type > 32000)
            txtmi = 0;

        if (txtmi == 0)
        {
            strcpy(txtspath, dirname);
            strcat(txtspath, "/");
            strcat(txtspath, entity->d_name);
            // printf("%s\n\t",txtspath);
            file = fopen(txtspath, "r");
            // char c = fgetc(file);
            // printf("%c\n",c);
            strcpy(txtadi, entity->d_name);

            memcpy(entity->d_name , entity->d_name , sizeof(entity->d_name)-4);
            for(y=0;etiket[y] !='\0' ;y++)
                y=y;
            memcpy(etiket , etiket+2 , y-4);



            if(entity->d_name == etiket)
            {
                while (fgets(dsysatir, 100, file) != NULL)
            {


                        for(int s=0;s<100;s++)
                        {
                            char *ara_ptr = strstr(dsysatir+p , "[[");
                           char *ara_ptr2 = strstr(ara_ptr , "]]");
                           etiketuzunluk = ara_ptr2 - ara_ptr+2;
                           memcpy(temp , ara_ptr , etiketuzunluk);
                            if(strcmp(temp , etiket)==0)
                            {
                                strcpy(temp , degistir);
                                memcpy(dsysatir[ara_ptr-dsysatir] , temp , etiketuzunluk);
                                p=ara_ptr2-dsysatir+2;
                                if (remove(entity->d_name)==0)
                                    printf("Dosya başarılı bir şekilde silindi!");
                                else
                                    perror("Dosya silme hatası");

                                rename(entity->d_name, degistir);
                                printf("%s",entity->d_name);

                            }
                        }



            }
            }


        }
        if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, ".."))
        {
            char path[100] = {0};
            strcat(path, dirname);
            strcat(path, "/");
            strcat(path, entity->d_name);
            Guncelle(path, etiket , degistir);
        }
    }

    closedir(dir);
}



char etiket[100][150];
int kacincietiket = 0;
void DosyayaYaz(const char *dirname)
{
    int txtmi = 1;
    char txtadi[100];
    char txtspath[100];
    char fileSatir[100];


    FILE *file;
    DIR *dir = opendir(dirname);

    struct dirent *entity;

    while ((entity = readdir(dir)) != NULL)
    {

        int k, l;

        int txtmi = 1;
        strcpy(txtadi, entity->d_name);


        if (strstr(txtadi, ".txt") != NULL)
        {
            strcpy(txtspath, dirname);
            strcat(txtspath, "/");
            strcat(txtspath, entity->d_name);
            printf("%s\n\t", txtspath);
            file = fopen(txtspath, "r");

            char *ara_ptr2;
            char *ara_ptr;
            printf("%s\n", txtadi);

            while (fgets(fileSatir, 100, file) != NULL)
            {

                for (k = 0; k < 2; k++)
                {
                    if (k > 0)
                        ara_ptr = strstr(ara_ptr2, "[[");
                    else
                        ara_ptr = strstr(fileSatir, "[[");
                    while (1)
                    {
                        ara_ptr2 = strstr(ara_ptr + 2, "]]");

                        if (ara_ptr2 != NULL)
                        {
                            int krktrsys = ara_ptr2 - ara_ptr;
                            memcpy(etiket[kacincietiket], ara_ptr + 2, krktrsys - 2);
                            printf("%s\n", etiket[kacincietiket]);
                            kacincietiket++;

                            break;
                        }
                        else
                            break;
                    }
                    ara_ptr = strstr(ara_ptr2 + 2, "[[");
                    if (ara_ptr != NULL)
                        k = 0;
                }
            }
        }

        if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, ".."))
        {
            char path[100] = {0};
            strcat(path, dirname);
            strcat(path, "/");
            strcat(path, entity->d_name);
            DosyayaYaz(path);
        }

    }


    closedir(dir);
}

void ListFiles(const char *dirname, char aranan[20])
{

    char txtspath[100] = {0};
    char txtadi[100] = {0};
    int i = 0;
    FILE *file;

    DIR *dir = opendir(dirname);

    //  printf("Dosyalar %s de okunuyor\n",dirname);

    struct dirent *entity;

    while ((entity = readdir(dir)) != NULL)
    {
        int txtmi = 1;
        int strsys = 0;
        int j = 0;
        int sonuc;
        char dsysatir[100];

        // printf("%d      %s          %s\n",entity->d_type , dirname , entity->d_name);

        if (entity->d_type < 33000 && entity->d_type > 32000)
            txtmi = 0;

        if (txtmi == 0)
        {
            strcpy(txtspath, dirname);
            strcat(txtspath, "/");
            strcat(txtspath, entity->d_name);
            // printf("%s\n\t",txtspath);
            file = fopen(txtspath, "r");
            // char c = fgetc(file);
            // printf("%c\n",c);
            strcpy(txtadi, entity->d_name);

            while (aranan[i] != '\0')
                i++;

            while (fgets(dsysatir, 100, file) != NULL)
            {
                strsys++;
                for (int m = 0; m < 100; m++)
                {

                    sonuc = 1;
                    sonuc = memcmp(dsysatir + m, aranan, i * 1);
                    if (sonuc == 0)
                    {
                        printf("Aradiginiz kelime %s de %d. satirda\n", txtadi, strsys);
                    }
                }
            }
            strsys = 0;
        }
        if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, ".."))
        {
            char path[100] = {0};
            strcat(path, dirname);
            strcat(path, "/");
            strcat(path, entity->d_name);
            ListFiles(path, aranan);
        }
    }

    closedir(dir);
}

int main()
{
    int secim;
    while (1)
    {
        printf("\n1:Arama \n");
        printf("2:Guncelleme \n");
        printf("3:Dosyaya Yazma \n");
        printf("0: cikis\n");
        printf("secim?: ");
        scanf("%d", &secim);
        char kelime[30];
        char gecicidsydizi[90];
        int strsys = 0;
        int i = 0;
        char aranan[20];
        char etiketiguncelle[20];
        char degistir[20];

        switch (secim)
        {
        case 0:
            exit(0);
        case 1:

            printf("Aranacak kelimeyi girin: ");
            scanf("%s", aranan);
            ListFiles(".", aranan);

            break;

        case 2:

            printf("Guncellencek etiketi giriniz");
            scanf("%s",&etiketiguncelle);
            printf("Aradiginiz etiketi ne ile guncellemek istiyorsunuz");
            scanf("%s",&degistir);
            Guncelle("." , etiketiguncelle , degistir);

            break;

        case 3:

            DosyayaYaz(".");
            for(int i=0;i<kacincietiket;i++)
                printf("%s",etiket[i]);
            break;

        default:
            printf("yanlis secim\n");
        }
    }
}






