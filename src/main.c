#include "test.h"


int main()
{
    int k;
    char *fichHTML=(char *)malloc(1000);
    donnees img,aud,vid,lien;

    do
    {
        menu();
        scanf("%d",&k);

        switch (k)
        {
            case 1:
                printf("Donnez le nom de fichier HTML:");
                scanf("%s",fichHTML);

                FILE* pf=fopen(fichHTML,"r");

                if(pf==NULL)
                    printf("\n!!!!!!ERREUR!!!!!!\n");
                else
                {
                    char c;

                    img.typeLiens="Images";
                    img.nbrRep=0;

                    aud.typeLiens="Audios";
                    aud.nbrRep=0;

                    vid.typeLiens="Videos";
                    vid.nbrRep=0;

                    lien.typeLiens="Liens ";
                    lien.nbrRep=0;


                    do
                    {
                        c=fgetc(pf);

                        if(c==60)
                        {
                            int i=1;
                            char *tag=(char*)calloc(10000000,sizeof(char));

                            tag[0]=60;
                            while(c!=62)
                            {
                                c=fgetc(pf);
                                tag[i]=c;
                                i++;
                            }

                            RepImg(tag,&img);
                            RepAud(tag,&aud);
                            RepVid(tag,&vid);
                            RepLien(tag,&lien);

                            free(tag);
                        }
                    }while(!feof(pf));

                    fclose(pf);

                    printf("\n\tTraitement termine\n");
                    system("pause");
                    system("cls");
                }
                break;

            case 2:
                fichStatistique(fichHTML,img,aud,vid,lien);
                system("pause");
                system("cls");
                break;

            case 3:
                PageStatHTML(fichHTML,img,aud,vid,lien);
                system("pause");
                system("cls");
                break;
        }
        
    }while(k!=4);

    return EXIT_SUCCESS;
}