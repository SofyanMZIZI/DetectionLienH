#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct donnees
{
    char *typeLiens;
    int nbrRep;
}donnees;


int RepImg(char *balise,donnees* img)
{
    char *ExtImg[7]={".jpeg",".png",".gif",".tiff",".svg",".bmp",".gpg"};
    char *bal[3]={"<img","<object","<embed"};

    for(int i=0;i<3;i++)
        for(int j=0;j<7;j++)
            if(strstr(balise,bal[i])!=NULL && strstr(balise,ExtImg[j])!=NULL)
                img->nbrRep++;
}


void RepAud(char *balise,donnees* aud)
{
    char *ExtAud[7]={".riff",".wav",".bwf",".ogg",".raw",".mp3","wma"};
    char *bal[3]={"<object","<embed"};

    for(int i=0;i<2;i++)
        for(int j=0;j<7;j++)
            if(strstr(balise,bal[i])!=NULL && strstr(balise,ExtAud[j])!=NULL)
                aud->nbrRep++;

    if(strstr(balise,"</audio>")!=NULL)
        aud->nbrRep++;
}


void RepVid(char *balise,donnees* vid)
{
    char *ExtVid[10]={".mp4",".avi",".webm",".mkv",".flv",".ogv",".wmv",".mpeg",".m4v","/embed/"};
    char *bal[3]={"<object","<embed"};

    for(int i=0;i<2;i++)
        for(int j=0;j<10;j++)
            if(strstr(balise,bal[i])!=NULL && strstr(balise,ExtVid[j])!=NULL)
                vid->nbrRep++;

    if(strstr(balise,"</video>")!=NULL || strstr(balise,"</iframe>")!=NULL)
        vid->nbrRep++;
}


void RepLien(char *balise,donnees* lien)
{
    if(strstr(balise,"</a>")!=NULL)
        lien->nbrRep++;
}


void menu()
{
    printf( "\t\tMENU\n"
            "1-Entrer le fichier texte HTML\n"
            "2-Afficher les statistiques sur le fichier texte\n"
            "3-Afficher les statistiques sur une page web\n"
            "4-Quitter\n"
            "\t\t\t\tVotre choix: ");
}


void fichStatistique(char fichHTML[],donnees img,donnees aud,donnees vid,donnees lien)
{
    FILE* pStat=fopen("Statistique.txt","w");

    if(pStat==NULL)
        printf("\nERREUR:Creation de fichier\n");
    else
    {
        fprintf(pStat,"\tSTATISTIQUES du \"%s\"\n%s %d\n%s %d\n%s %d\n%s %d"
        ,fichHTML,img.typeLiens,img.nbrRep,aud.typeLiens,aud.nbrRep,vid.typeLiens,vid.nbrRep
        ,lien.typeLiens,lien.nbrRep);
        printf("\n\tEcriture dans \"Statistique.txt\" faite\n");
    }
}


void PageStatHTML(char fichHTML[],donnees img,donnees aud,donnees vid,donnees lien)
{
    FILE* pHTML=fopen("index.html","w");

    if(pHTML==NULL)
        printf("\nERREUR:Creation de fichier\n");
    else
    {
        fprintf(pHTML,  "<!DOCTYPE html>\n"
                        "<html>\n\t"
                        "<head>\n\t\t"        
                        "<meta charset=\"utf-8\" />\n\t\t"
                        "<title>RESULTAT</title>\n\t"
                        "</head>\n\t"
                        "<body>\n\t\t"
                        "<h2 style=\"text-align:center;\">Statistiques du page HTML: \"%s\"</h2>\n\t\t"

                        "<table border=\"5\" width=\"70%%\" align=\"center\">\n\t\t\t"
                        "<tr style=\"text-align:center; font-weight: bold;\">\n\t\t\t\t"
                        "<td>Type du lien</td>\n\t\t\t\t"
                        "<td>Nombres</td>\n\t\t\t"
                        "</tr>\n\t\t\t\t"
                        "<tr>\n\t\t\t\t"
                        "<td>liens Image</td>\n\t\t\t\t\t"
                        "<td align=\"center\">%d</td>\n\t\t\t\t"
                        "</tr>\n\t\t\t\t"
                        "<tr>\n\t\t\t\t"
                        "<td>liens Audio</td>\n\t\t\t\t"
                        "<td align=\"center\">%d</td>\n\t\t\t"
                        "</tr>\n\t\t\t"
                        "<tr>\n\t\t\t\t"
                        "<td>liens Video</td>\n\t\t\t\t"
                        "<td align=\"center\">%d</td>\n\t\t\t"
                        "</tr>\n\t\t\t"
                        "<tr>\n\t\t\t\t"
                        "<td>liens Hypertextes vers une autre page web</td>\n\t\t\t\t"
                        "<td align=\"center\">%d</td>\n\t\t\t"
                        "</tr>\n\t\t"
                        "</table>\n\t" 
                        "</body>\n"
                        "</html>",fichHTML,img.nbrRep,aud.nbrRep,vid.nbrRep,lien.nbrRep);
        printf("\n\tCreation du page web faite.\n");
    }
}