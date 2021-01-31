#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct elem_arbre
{
    char nom[20];
    char type;//V : Volume F : Fichier R : Repertoire
    struct elem_arbre *fils;
    struct elem_arbre *frere;
}
elem_arbre;

typedef struct liste_rep
{
    elem_arbre *rep;
    int pos;
    struct liste_rep *suiv;
    struct liste_rep *prec;
}
liste_rep;

typedef struct liste_volume
{
    elem_arbre *vol;
    struct liste_volume *suiv;
}
liste_volume;

typedef struct chemin
{
    char contenu[30];
    struct chemin *suiv;
}
chemin;

typedef struct pile
{
    elem_arbre *elm;
    struct pile *bas;
} pile;

elem_arbre* initialiser(elem_arbre*rac)
{
    rac=(elem_arbre*)malloc(sizeof(elem_arbre));
    strcpy(rac->nom,"pc");
    rac->fils=NULL;
    rac->frere=NULL;
    rac->type='d';
    return rac;
}

int EstVide(pile *p)
{
    if(p->bas==NULL)
        return 1;
    else
        return 0;
}

pile* Empiler(pile*p,elem_arbre *elem)
{

    pile *s=(pile*)malloc(sizeof(pile));
    s->elm=elem;
    s->bas=p;
    return s;

}

typedef struct pileval
{
    int val;
    struct pileval *bas;
} pileval;

int EstVideval(pileval *p)
{
    if(p->bas==NULL)
        return 1;
    else
        return 0;
}

pileval* Empilerval(pileval*p,int val)
{
    pileval *s=(pileval*)malloc(sizeof(pileval));
    s->val=val;
    s->bas=p;
    return s;
}

int redandonce_nom(elem_arbre *rac,elem_arbre *noeud3,char *nom)
{
    pile *k;
    int stop=0;
    elem_arbre *noeud=rac;
    elem_arbre *p;
    pile *ppp=(pile*)malloc(sizeof(pile));
    ppp->elm=NULL;
    ppp->bas=NULL;


    do
    {
        if(noeud->fils!=NULL&&noeud->frere!=NULL)
        {
            ppp=Empiler(ppp,noeud);
        }

        if(noeud->fils!=NULL)
        {

            for(p=noeud->fils; p!=NULL&&p!=noeud3;)
            {
                p=p->frere;
            }

            if(p==noeud3)
            {
                p=noeud->fils;

                while(p->frere!=NULL&&strcmp(p->nom,nom)!=0)
                {
                    p=p->frere;
                }

                if(p->frere==NULL&&strcmp(p->nom,nom)!=0)
                    return 0;
                else
                    return 1;
            }

            noeud=noeud->fils;
        }
        else
        {
            if(noeud->frere!=NULL)
            {
                noeud=noeud->frere;
            }
            else
            {

                if(EstVide(ppp)!=1)
                {
                    noeud=ppp->elm->frere;
                    k=ppp;
                    ppp=ppp->bas;
                    free(k);
                }
                else
                {
                    k=ppp;
                    ppp=ppp->bas;
                    free(k);
                    stop=1;
                }

            }
        }
    }
    while(stop!=1);



    return 0;

}

void afficher_itter(elem_arbre rac,liste_rep *lrep)
{
    pile *k;
    int stop=0;
    int i;
    liste_rep *q,*kkkk;
    elem_arbre *noeud=&rac;
    liste_rep *jjjj;
    liste_rep *ptr1,*ptr2,*ptr3;
    int cpt=0;
    pileval*pv=NULL;
    pile *ppp=(pile*)malloc(sizeof(pile));
    ppp->elm=NULL;
    ppp->bas=NULL;

    printf("\n");

    do
    {

        if(lrep==NULL)
        {
            lrep=(liste_rep*)malloc(sizeof(liste_rep));
            lrep->rep=noeud;
            lrep->prec=NULL;
            lrep->suiv=NULL;
            lrep->pos=cpt;
            kkkk=lrep;
        }
        else
        {
            q =(liste_rep*)malloc(sizeof(liste_rep));
            q->rep=noeud;
            q->prec=kkkk;
            q->suiv=NULL;
            kkkk->suiv=q;
            kkkk=kkkk->suiv;
            kkkk->pos=cpt;
        }

        if(noeud->fils!=NULL&&noeud->frere!=NULL)
        {
            ppp=Empiler(ppp,noeud);
        }


        if(noeud->fils!=NULL)
        {
            noeud=noeud->fils;
            pv=Empilerval(pv,cpt);
            cpt=cpt+1;
        }
        else
        {
            if(noeud->frere!=NULL)
            {
                noeud=noeud->frere;
            }
            else
            {

                if(EstVide(ppp)!=1)
                {

                    jjjj=lrep;
                    while(jjjj!=NULL&&ppp!=NULL&&jjjj->rep!=ppp->elm)
                    {
                        jjjj=jjjj->suiv;
                    }

                    if(jjjj!=NULL)
                        cpt=jjjj->pos;

                    noeud=ppp->elm->frere;
                    k=ppp;
                    ppp=ppp->bas;
                    free(k);
                }
                else
                {
                    k=ppp;
                    ppp=ppp->bas;
                    free(k);
                    stop=1;
                }

            }
        }
    }
    while(stop!=1);


    ptr1=lrep;

    do
    {
        printf("\n");
        for(i=0; i<ptr1->pos; i++)
        {
            ptr2=lrep;
            ptr3=lrep;

            while(ptr2!=NULL&&ptr2!=ptr1)
            {
                if(ptr2->pos==i)
                {
                    ptr3=ptr2;
                }
                ptr2=ptr2->suiv;
            }


            if(ptr3->rep->frere!=NULL)
                putchar(179);
            else
                printf(" ");

            printf("  ");
        }

        if(ptr1->rep->frere!=NULL)
            putchar(195);
        else
            putchar(192);
        putchar(196);
        printf("%s",ptr1->rep->nom);
        ptr1=ptr1->suiv;
    }
    while(ptr1!=NULL);
}

void creer_fils_frere(elem_arbre *noeud,elem_arbre *rac)
{
    int rep,choix,repeter;
    char nom[20];

    if(noeud->type=='f')
    {
        noeud->fils=NULL;
        printf("\nY a t il autre chose %c c%ct%c du fichier %s ? O/N : ",133,147,130,noeud->nom);
        do
        {
            rep=getch();
        }
        while(rep!=79&&rep!=111&&rep!=78&&rep!=110);// 79O 111o 78N 110n

        if(rep==78||rep==110)
        {
            noeud->frere=NULL;
        }
        else
        {
            printf("\nQuel est son type ? ");
            printf("\nF- Fichier ");
            printf("\nR- R%cpertoire ",130);
            printf("\nVotre choix : ");

            do
            {
                choix=getch();
            }
            while(choix!=70&&choix!=102&&choix!=82&&choix!=114);// 70F 102f 82R 114r

            noeud->frere=(elem_arbre*)malloc(sizeof(elem_arbre));
            noeud->frere->fils=NULL;
            noeud->frere->frere=NULL;
            if(choix==70||choix==102)//fichier
            {
                do
                {
                    printf("\nDonnez le nom du fichier : ");
                    gets(nom);
                    repeter=redandonce_nom(rac,noeud,nom);
                    if(repeter==1)
                        printf("Il vaut mieux changer de nom SVP !!");
                }
                while(strcmp(nom,"\0")==0||repeter==1);

                strcpy(noeud->frere->nom,nom);
                noeud->frere->type='f';
            }
            else//repertoire
            {
                printf("\nDonnez le nom du r%cpertoire : ",130);

                do
                {
                    gets(noeud->frere->nom);
                }
                while(strcmp(noeud->frere->nom,"\0")==0);

                noeud->frere->type='r';
            }
            creer_fils_frere(noeud->frere,rac);
        }
    }
    else
    {
        printf("\nY a t il du contenu dans le rep%crtoire %s ? O/N : ",130,noeud->nom);
        do
        {
            rep=getch();
        }
        while(rep!=79&&rep!=111&&rep!=78&&rep!=110);// 79O 111o 78N 110n

        if(rep==78||rep==110)
        {
            noeud->fils=NULL;
        }
        else
        {
            printf("\nQuel est son type ? ");
            printf("\nF- Fichier ");
            printf("\nR- R%cpertoire ",130);
            printf("\nVotre choix : ");

            do
            {
                choix=getch();
            }
            while(choix!=70&&choix!=102&&choix!=82&&choix!=114);// 70F 102f 82R 114r

            noeud->fils=(elem_arbre*)malloc(sizeof(elem_arbre));
            noeud->fils->fils=NULL;
            noeud->fils->frere=NULL;
            if(choix==70||choix==102)//fichier
            {
                printf("\nDonnez le nom du fichier : ");

                do
                {
                    gets(noeud->fils->nom);
                }
                while(strcmp(noeud->fils->nom,"\0")==0);
                noeud->fils->type='f';
            }
            else//repertoire
            {
                printf("\nDonnez le nom du r%cpertoire : ",130);

                do
                {

                    gets(noeud->fils->nom);

                }
                while(strcmp(noeud->fils->nom,"\0")==0);

                noeud->fils->type='r';
            }
            creer_fils_frere(noeud->fils,rac);
        }

        printf("\nY a t il autre chose %c c%ct%c du rep%crtoire %s ? O/N : ",133,147,130,130,noeud->nom);
        do
        {
            rep=getch();
        }
        while(rep!=79&&rep!=111&&rep!=78&&rep!=110);// 79O 111o 78N 110n

        if(rep==78||rep==110)
        {
            noeud->frere=NULL;
        }
        else
        {
            printf("\nQuel est son type ? ");
            printf("\nF- Fichier ");
            printf("\nR- R%cpertoire ",130);
            printf("\nVotre choix : ");

            do
            {
                choix=getch();
            }
            while(choix!=70&&choix!=102&&choix!=82&&choix!=114);// 70F 102f 82R 114r

            noeud->frere=(elem_arbre*)malloc(sizeof(elem_arbre));
            noeud->frere->fils=NULL;
            noeud->frere->fils=NULL;

            if(choix==70||choix==102)//fichier
            {
                do
                {
                    printf("\nDonnez le nom du fichier : ");
                    gets(nom);
                    repeter=redandonce_nom(rac,noeud,nom);
                    if(repeter==1)
                        printf("Il vaut mieux changer de nom SVP !!");
                }
                while(strcmp(nom,"\0")==0||repeter==1);
                strcpy(noeud->frere->nom,nom);
                noeud->frere->type='f';
            }
            else//repertoire
            {
                printf("\nDonnez le nom du r%cpertoire : ",130);

                do
                {

                    gets(noeud->frere->nom);

                }
                while(strcmp(noeud->frere->nom,"\0")==0);
                noeud->frere->type='r';
            }
            creer_fils_frere(noeud->frere,rac);
        }
    }
}

int nbr_elem(elem_arbre *elm,char *nom)
{
    if(elm==NULL)
    {
        return 0;
    }
    else
    {
        if(strcmp(elm->nom,nom)==0)
            return 1 + nbr_elem(elm->fils,nom)+nbr_elem(elm->frere,nom);
        else
            return nbr_elem(elm->fils,nom)+nbr_elem(elm->frere,nom);
    }
}

elem_arbre* chercher_elem(char *chem,elem_arbre *rac)
{
    chemin *first=NULL,*last,*elem;
    char *part;
    char seps[]= "\\";
    elem_arbre *noeud=rac;
    int stop=0,trouve;

    part = strtok(chem,seps);

    while(part!=NULL)
    {
        elem=(chemin*)malloc(sizeof(chemin));
        strcpy(elem->contenu,part);
        elem->suiv=NULL;

        if(first==NULL)
        {
            first=elem;
            last=elem;
        }
        else
        {
            last->suiv=elem;
            last=elem;
        }

        part = strtok(NULL,seps);
    }

    do
    {
        if(strcmp(noeud->nom,first->contenu)==0)
        {
            first=first->suiv;
            if(first!=NULL)
            {
                noeud=noeud->fils;
            }
            else
            {
                trouve=1;
                stop=1;
            }
        }
        else
        {
            if(noeud->frere!=NULL)
            {
                noeud=noeud->frere;
            }
            else
            {
                stop=1;
                trouve=0;

            }
        }

    }
    while(stop!=1);

    if(trouve==0)
        return NULL;
    else
        return noeud;

}

elem_arbre* chercher_pere_d1_elem(char *chem,elem_arbre *rac)
{
    chemin *first=NULL,*last,*elem;
    char *part;
    char seps[]= "\\";
    elem_arbre *noeud=rac;
    elem_arbre *prec;
    int stop=0,trouve;

    part = strtok(chem,seps);


    while(part!=NULL)
    {
        elem=(chemin*)malloc(sizeof(chemin));
        strcpy(elem->contenu,part);
        elem->suiv=NULL;

        if(first==NULL)
        {
            first=elem;
            last=elem;
        }
        else
        {
            last->suiv=elem;
            last=elem;
        }

        part = strtok(NULL,seps);
    }

    do
    {
        if(strcmp(noeud->nom,first->contenu)==0)
        {
            first=first->suiv;
            if(first!=NULL)
            {
                prec=noeud;
                noeud=noeud->fils;
            }
            else
            {
                trouve=1;
                stop=1;
            }
        }
        else
        {
            if(noeud->frere!=NULL)
            {
                prec=noeud;
                noeud=noeud->frere;
            }
            else
            {
                stop=1;
                trouve=0;

            }
        }

    }
    while(stop!=1);

    if(trouve==0)
        return NULL;
    else
        return prec;

}

void ajouter_nv_elem(elem_arbre *rac)
{
    char chem[200],nom[10];
    int choix,rep,repeter;
    elem_arbre *noeud,*nvelem;
    liste_rep *lrep=NULL;

    printf("\n");
    afficher_itter(*rac,lrep);
    printf("\n");

    printf("\nDonnez le chemin d'un R%cpertoir ou Volume dans lequel vous voulez mettre le nouveau contenu : \n",130);
    gets(chem);

    noeud=chercher_elem(chem,rac);


    if(noeud!=NULL)
    {
        if(noeud->type=='f')
        {
            printf("\nCeci est le chemin d'un fichier et non pas R%cpertoire ou Volume !!",130,130);
            getch();
        }
        else
        {
            if(noeud->type=='d')
            {
                printf("\nCeci est le chemin de votre disque et non pas R%cpertoire ou Volume !!",130,130);
                getch();
            }
            else
            {
                printf("\nQuel est le type du nouveau contenu ? ");
                printf("\nF- Fichier ");
                printf("\nR- R%cpertoire ",130);
                printf("\nVotre choix : ");

                do
                {
                    choix=getch();
                }
                while(choix!=70&&choix!=102&&choix!=82&&choix!=114);// 70F 102f 82R 114r

                nvelem=(elem_arbre*)malloc(sizeof(elem_arbre));
                if(choix==70||choix==102)//fichier
                {
                    do
                    {
                        printf("\nDonnez le nom du fichier : ");
                        gets(nom);
                        repeter=redandonce_nom(rac,noeud->fils,nom);
                        if(repeter==1)
                            printf("Il vaut mieux changer de nom SVP !!");
                    }
                    while(strcmp(nom,"\0")==0||repeter==1);
                    strcpy(nvelem->nom,nom);
                    nvelem->type='f';
                }
                else//repertoire
                {
                    do
                    {
                        printf("\nDonnez le nom du r%cpertoire : ",130);
                        gets(nom);
                        repeter=redandonce_nom(rac,noeud->fils,nom);
                        if(repeter==1)
                            printf("Il vaut mieux changer de nom SVP !!");
                    }
                    while(strcmp(nom,"\0")==0||repeter==1);
                    strcpy(nvelem->nom,nom);

                    nvelem->type='r';
                }
                nvelem->fils=NULL;
                nvelem->frere=NULL;

                if(noeud->fils==NULL)
                {
                    noeud->fils=nvelem;
                }
                else
                {
                    noeud=noeud->fils;

                    while(noeud->frere!=NULL)
                    {
                        noeud=noeud->frere;
                    }

                    noeud->frere=nvelem;
                }
                printf("Nouveau %cl%cment ajout%c avec succ%cs !!",130,130,130,138);

                printf("\n");
                afficher_itter(*rac,lrep);
                printf("\n");

                do
                {
                    noeud=nvelem;
                    printf("\nY a t il autre chose %c ajouter dans ce chemin ? O/N : ",133);
                    do
                    {
                        rep=getch();
                    }
                    while(rep!=79&&rep!=111&&rep!=78&&rep!=110);// 79O 111o 78N 110n

                    if(rep==79||rep==111)
                    {
                        printf("\nQuel est le type du nouveau contenu ? ");
                        printf("\nF- Fichier ");
                        printf("\nR- R%cpertoire ",130);
                        printf("\nVotre choix : ");

                        do
                        {
                            choix=getch();
                        }
                        while(choix!=70&&choix!=102&&choix!=82&&choix!=114);// 70F 102f 82R 114r

                        nvelem=(elem_arbre*)malloc(sizeof(elem_arbre));
                        if(choix==70||choix==102)//fichier
                        {
                            printf("\nDonnez le nom du fichier : ");

                            do
                            {
                                gets(nvelem->nom);
                            }
                            while(strcmp(nvelem->nom,"\0")==0);
                            nvelem->type='f';
                        }
                        else//repertoire
                        {
                            printf("\nDonnez le nom du r%cpertoire : ",130);

                            do
                            {
                                gets(nvelem->nom);
                            }
                            while(strcmp(nvelem->nom,"\0")==0);
                            nvelem->type='r';
                        }
                        nvelem->fils=NULL;
                        nvelem->frere=NULL;
                        noeud->frere=nvelem;
                        printf("Nouveau %cl%cment ajout%c avec succ%cs !!",130,130,130,138);


                        printf("\n");
                        afficher_itter(*rac,lrep);
                        printf("\n");
                    }
                }
                while(rep!=78&&rep!=110);
            }
        }
    }
    else
    {
        printf("\nChemin erron%c !!",130);
        getch();
    }


}

void suppression(elem_arbre *elem)
{
    if(elem->fils!=NULL)
        suppression(elem->fils);
    if(elem->frere!=NULL)
        suppression(elem->frere);

    free(elem);
}

void supprimer_elem(elem_arbre *rac)
{
    char chem[200],chem2[200];
    int rep;
    elem_arbre *noeud,*prec;
    liste_rep *lrep=NULL;

    if(rac==NULL)
    {
        printf("Il n y a rien %c supprimer !!",133);
    }
    else
    {
        printf("\n");
        afficher_itter(*rac,lrep);
        printf("\n");

        printf("\nDonnez le chemin de l'%cl%cment que vous voulez supprimer : \n",130,130);
        gets(chem);

        strcpy(chem2,chem);

        noeud=chercher_elem(chem,rac);

        if(noeud!=rac)
            prec=chercher_pere_d1_elem(chem2,rac);

        if(noeud==NULL)
        {
            printf("Chemin erron%c !!",130);
            getch();
        }
        else
        {

            if(noeud->type=='f')
                printf("\nEtes vous s%cr de vouloir supprimer ce fichier ? O/N : ",150);
            else
            {
                if(noeud->type=='v')
                    printf("\nEtes vous s%cr de vouloir supprimer ce volume ? O/N : ",150);
                else
                {
                    if(noeud->type=='r')
                        printf("\nEtes vous s%cr de vouloir supprimer ce r%cpertoire ? O/N : ",150,130);
                    else
                        printf("\nEtes vous s%cr de vouloir formater ce disque ? O/N : ",150);
                }
            }

            do
            {
                rep=getch();
            }
            while(rep!=111&&rep!=110&&rep!=78&&rep!=79);

            if(rep==78||rep==110)
            {
                printf("\nAucune op%cration n'a %ct%c effectu%ce ",130,130,130,130);
                getch();
            }
            else
            {

                if(noeud==rac)
                {
                    suppression(rac->fils);
                    rac->fils=NULL;
                }
                else
                {
                    if(noeud==prec->fils)
                        prec->fils=noeud->frere;
                    else
                        prec->frere=noeud->frere;

                    if(noeud->fils!=NULL)
                        suppression(noeud->fils);
                    free(noeud);
                }
                printf("\nSuppression r%cussie !!",130,130,130);

                if(rac->fils!=NULL)
                {
                    printf("\n");
                    afficher_itter(*rac,lrep);
                    printf("\n");
                    printf("\nAppuyez sur une touche pour continuer");
                }
                getch();
            }
        }
    }
}

void supprimer_elem_couper(elem_arbre *rac,char *chem3)
{
    char chem2[200];
    elem_arbre *noeud,*prec;

    strcpy(chem2,chem3);

    noeud=chercher_elem(chem3,rac);
    prec=chercher_pere_d1_elem(chem2,rac);

    if(noeud==rac)
    {
        suppression(rac);
        rac=NULL;
    }
    else
    {
        if(noeud==prec->fils)
            prec->fils=noeud->frere;
        else
            prec->frere=noeud->frere;

        if(noeud->fils!=NULL)
            suppression(noeud->fils);
        free(noeud);
    }
}

void annuler_un_enreg(elem_arbre *noeud)
{

    if(noeud->fils!=NULL)
        suppression(noeud->fils);
    free(noeud);

}

void ajouter_vol(elem_arbre *rac)
{
    int choix,repeter,rep;
    elem_arbre *elem,*p,*k;
    char nom[20];

    if(rac->fils==NULL)
    {
        elem=(elem_arbre*)malloc(sizeof(elem_arbre));
        rac->fils=elem;
        printf("\nDonnez le nom de votre nouveau volume : ");
        do
        {
            gets(elem->nom);
        }
        while(strcmp(elem->nom,"\0")==0);
        k=rac;
    }
    else
    {
        for(p=rac->fils; p->frere!=NULL; p=p->frere);

        do
        {
            printf("\nDonnez le nom de votre nouveau volume : ");
            gets(nom);
            repeter=redandonce_nom(rac,p,nom);
            if(repeter==1)
                printf("Il vaut mieux changer de nom SVP !!");
        }
        while(strcmp(nom,"\0")==0||repeter==1);

        elem=(elem_arbre*)malloc(sizeof(elem_arbre));
        strcpy(elem->nom,nom);
        p->frere=elem;
        k=p;
    }

    elem->frere=NULL;
    elem->type='v';
    printf("\nQuel est le contenu de votre volume  ? ");
    printf("\nF- Fichier ");
    printf("\nR- R%cpertoire ",130);
    printf("\nV- Vide ");
    printf("\nVotre choix : ");

    do
    {
        choix=getch();
    }
    while(choix!=70&&choix!=102&&choix!=82&&choix!=114&&choix!=86&&choix!=118);// 70F 102f 82R 114r 86V 118v

    if(choix==86||choix==118)//vide
    {
        elem->fils=NULL;
    }
    else
    {
        elem->fils=(elem_arbre*)malloc(sizeof(elem_arbre));
        if(choix==70||choix==102)//fichier
        {
            printf("\nDonnez le nom du fichier : ");

            do
            {
                gets(elem->fils->nom);
            }
            while(strcmp(elem->fils->nom,"\0")==0);
            elem->fils->type='f';
        }
        else//repertoire
        {
            printf("\nDonnez le nom du r%cpertoire : ",130);
            do
            {

                gets(elem->fils->nom);

            }
            while(strcmp(elem->nom,"\0")==0);
            elem->fils->type='r';
        }
        creer_fils_frere(elem->fils,rac);
    }


    printf("\nEtes vous s%cr de vouloir enregistrer ce volume ? O/N : ",150);
    do
    {
        rep=getch();
    }
    while(rep!=111&&rep!=110&&rep!=78&&rep!=79);

    if(rep==110||rep==78)
    {
        if(k==rac)
        {
            annuler_un_enreg(k->fils);
            rac->fils=NULL;
        }
        else
        {
            annuler_un_enreg(k->frere);
            k->frere=NULL;
        }
        printf("\nEnregistrement du volume annul%c ",130);
    }
    else
    {
        printf("\nNouveau volume ajout%c avec succ%cs !!",130,138);
    }
    getch();

}

void contenu_reprt_volume(elem_arbre *rac)
{
    elem_arbre *noeud,*noeud2;
    pile *k;
    int stop=0;
    int nbrelem=0;
    int nbrreprt=0;
    int nbrfich=0;
    int nbrfils;
    char chem[100];
    char chem2[100];
    pile *ppp=(pile*)malloc(sizeof(pile));
    liste_rep *lrep=NULL;

    chemin *first=NULL,*last,*elem,*ptr;
    ppp->elm=NULL;
    ppp->bas=NULL;

    printf("\n");
    afficher_itter(*rac,lrep);
    printf("\n");

    printf("\nDonnez le chemin d'un volume ou r%cpertoire que vous voulez afficher son contenu : \n",130);
    gets(chem);
    strcpy(chem2,chem);

    noeud=chercher_elem(chem,rac);

    if(noeud==NULL)
    {
        printf("Ce chemin est erron%c !!",130);
        getch();
    }
    else
    {
        if(noeud->type=='f'||noeud->type=='d')
        {
            if(noeud->type=='f')
                printf("\nCeci est le chemin d'un fichier et non pas volume ou r%cpertoire !!",130);
            else
                printf("\nCeci est le chemin de votre disque et non pas volume ou r%cpertoire !!",130);
            getch();
        }
        else
        {
            if(noeud->fils==NULL)
            {
                if(noeud->type=='v')
                    printf("\nCe volume est vide !! ");
                else
                    printf("\nCe r%cpertoire est vide !! ",130);

                getch();
            }
            else
            {
                if(noeud->type=='v')
                    printf("\nOn trouve dans ce volume les %cl%cments suivants : ",130,130);
                else
                    printf("\nOn trouve dans ce r%cpertoire les %cl%cments suivants : ",130,130,130);

                nbrfils=0;
                noeud2=noeud->fils;

                while(noeud2!=NULL)
                {
                    nbrfils++;
                    printf("\n%s\t: ",noeud2->nom);
                    printf("%s\\",chem2);
                    printf("%s",noeud2->nom);
                    noeud2=noeud2->frere;
                }

                if(noeud->type=='v')
                    printf("\n\nOn trouve %c partir de ce volume les %cl%cments suivants : ",133,130,130);
                else
                    printf("\n\nOn trouve %c partir de ce r%cpertoire les %cl%cments suivants : ",133,130,130,130);

                noeud2=noeud->fils;

                do
                {
                    nbrelem++;

                    if(noeud2->type=='f')
                        nbrfich++;
                    else
                        nbrreprt++;

                    printf("\n%s\t: %s\\",noeud2->nom,chem2);

                    if(noeud2->fils==NULL)
                    {
                        ptr=first;
                        while(ptr!=NULL)
                        {
                            printf("%s\\",ptr->contenu);
                            ptr=ptr->suiv;
                        }
                        printf("%s",noeud2->nom);

                    }

                    if(noeud2->fils!=NULL&&noeud2->frere!=NULL)
                    {
                        ppp=Empiler(ppp,noeud2);
                    }

                    if(noeud2->fils!=NULL)
                    {
                        elem=(chemin*)malloc(sizeof(chemin));
                        strcpy(elem->contenu,noeud2->nom);
                        elem->suiv=NULL;

                        if(first==NULL)
                        {
                            first=elem;
                            last=elem;
                        }
                        else
                        {
                            last->suiv=elem;
                            last=elem;
                        }

                        ptr=first;

                        while(ptr!=NULL)
                        {
                            if(ptr->suiv==NULL)
                                printf("%s",ptr->contenu);
                            else
                                printf("%s\\",ptr->contenu);

                            ptr=ptr->suiv;
                        }

                        noeud2=noeud2->fils;
                    }
                    else
                    {
                        if(noeud2->frere!=NULL)
                        {
                            noeud2=noeud2->frere;
                        }
                        else
                        {

                            if(EstVide(ppp)!=1)
                            {
                                noeud2=ppp->elm->frere;
                                k=ppp;
                                ppp=ppp->bas;
                                free(k);
                            }
                            else
                            {
                                k=ppp;
                                ppp=ppp->bas;
                                free(k);
                                stop=1;
                            }

                            if(first!=NULL)
                            {
                                if(first==last)
                                {
                                    first=NULL;
                                    last=NULL;
                                    free(ptr);
                                }
                                else
                                {
                                    ptr=first;

                                    while(ptr->suiv!=last)
                                    {
                                        ptr=ptr->suiv;
                                    }
                                    last=ptr;
                                    free(ptr->suiv);
                                    last->suiv=NULL;
                                }
                            }
                        }
                    }
                }
                while(stop!=1);

                if(noeud->type=='v')
                {
                    printf("\n\nNombre de fils dans ce volume\t\t\t\t     : %d",nbrfils);
                    printf("\nNombre total de tous les %cl%cments %c partir de ce volume      : %d",130,130,133,nbrelem);
                    printf("\nNombre total de tous les fichiers %c partir de ce volume      : %d",133,nbrfich);
                    printf("\nNombre total de tous les r%cpertoires %c partir de ce volume   : %d",130,133,nbrreprt);
                }
                else
                {
                    printf("\n\nNombre de fils dans ce r%cpertoire\t\t\t\t : %d",130,nbrfils);
                    printf("\nNombre total de tous les %cl%cments dans ce r%cpertoire             : %d",130,130,130,nbrelem);
                    printf("\nNombre total de tous les fichiers %c partir de ce r%cpertoire      : %d",133,130,nbrfich);
                    printf("\nNombre total de tous les r%cpertoires %c partir de ce r%cpertoire   : %d",130,133,130,nbrreprt);
                }
                printf("\n\nAppuyez sur n'importe quelle touche pour continuer");
                getch();
            }
        }
    }

}

void contenu_disque(elem_arbre *rac)
{
    elem_arbre *noeud2;
    pile *k;
    int stop=0;
    int nbrelem=0;
    int nbrreprt=0;
    int nbrfich=0;
    int nbrfils;
    char nom2[10];

    pile *ppp=(pile*)malloc(sizeof(pile));

    chemin *first=NULL,*last,*elem,*ptr,*rrr;
    ppp->elm=NULL;
    ppp->bas=NULL;


    printf("\n\nOn trouve dans ce disque les %cl%cments suivants : ",130,130);

    nbrfils=0;
    noeud2=rac->fils;

    while(noeud2!=NULL)
    {
        nbrfils++;
        printf("\n%s\t: ",noeud2->nom);
        printf("%s\\",rac->nom);
        printf("%s",noeud2->nom);
        noeud2=noeud2->frere;
    }

    printf("\n\nOn trouve %c partir de ce disque les %cl%cments suivants : ",133,130,130);

    noeud2=rac->fils;


    do
    {
        nbrelem++;

        if(noeud2->type=='f')
            nbrfich++;
        else
        {
            if(noeud2->type=='r')
                nbrreprt++;
        }

        printf("\n%s\t: %s\\",noeud2->nom,rac->nom);

        if(noeud2->fils==NULL)
        {
            ptr=first;
            while(ptr!=NULL)
            {
                printf("%s\\",ptr->contenu);
                ptr=ptr->suiv;
            }
            printf("%s",noeud2->nom);

        }

        if(noeud2->fils!=NULL&&noeud2->frere!=NULL)
        {
            ppp=Empiler(ppp,noeud2);
        }

        if(noeud2->fils!=NULL)
        {
            elem=(chemin*)malloc(sizeof(chemin));
            strcpy(elem->contenu,noeud2->nom);
            elem->suiv=NULL;

            if(first==NULL)
            {
                first=elem;
                last=elem;
            }
            else
            {
                last->suiv=elem;
                last=elem;
            }

            ptr=first;
            while(ptr!=NULL)
            {
                if(ptr->suiv==NULL)
                    printf("%s",ptr->contenu);
                else
                    printf("%s\\",ptr->contenu);

                ptr=ptr->suiv;
            }

            noeud2=noeud2->fils;
        }
        else
        {
            if(noeud2->frere!=NULL)
            {
                noeud2=noeud2->frere;
            }
            else
            {
                if(EstVide(ppp)!=1)
                {
                    strcpy(nom2,ppp->elm->nom);
                    noeud2=ppp->elm->frere;
                    k=ppp;
                    ppp=ppp->bas;
                    free(k);
                }
                else
                {
                    k=ppp;
                    ppp=ppp->bas;
                    free(k);
                    stop=1;
                }

                if(first!=NULL&&stop!=1)
                {
                    if(first==last)
                    {
                        first=NULL;
                        last=NULL;
                        free(ptr);
                    }
                    else
                    {
                        ptr=first;

                        if(strcmp(ptr->contenu,nom2)==0)
                        {
                            while(ptr!=NULL)
                            {
                                rrr=ptr;
                                ptr=ptr->suiv;
                                free(rrr);
                            }

                            first=NULL;
                            last=NULL;
                        }
                        else
                        {
                            while(ptr!=NULL&&strcmp(ptr->suiv->contenu,nom2)!=0)
                            {
                                ptr=ptr->suiv;
                            }

                            if(ptr!=NULL)
                            {
                                last=ptr;
                                free(ptr->suiv);
                                last->suiv=NULL;
                            }
                        }
                    }
                }
            }
        }
    }
    while(stop!=1);

    printf("\n\nNombre de volume dans ce disque\t\t\t\t     : %d",nbrfils);
    printf("\nNombre total de tous les %cl%cments %c partir de ce disque      : %d",130,130,133,nbrelem);
    printf("\nNombre total de tous les fichiers %c partir de ce disque      : %d",133,nbrfich);
    printf("\nNombre total de tous les r%cpertoires %c partir de ce disque   : %d",130,133,nbrreprt);

}


int existence_d_un_elem_ds_un_volrprt(elem_arbre*rac,elem_arbre *elem_cherch)
{
    pile *k;
    int stop=0;
    pile *ppp=(pile*)malloc(sizeof(pile));
    elem_arbre *noeud2;
    ppp->elm=NULL;
    ppp->bas=NULL;



    noeud2=rac->fils;

    do
    {
        if(noeud2==elem_cherch)
            return 1;

        if(noeud2->fils!=NULL&&noeud2->frere!=NULL)
        {
            ppp=Empiler(ppp,noeud2);
        }

        if(noeud2->fils!=NULL)
        {
            noeud2=noeud2->fils;
        }
        else
        {
            if(noeud2->frere!=NULL)
            {
                noeud2=noeud2->frere;
            }
            else
            {
                if(EstVide(ppp)!=1)
                {
                    noeud2=ppp->elm->frere;
                    k=ppp;
                    ppp=ppp->bas;
                    free(k);
                }
                else
                {
                    k=ppp;
                    ppp=ppp->bas;
                    free(k);
                    stop=1;
                }
            }
        }
    }
    while(stop!=1);

    return 0;
}

void nbr_occur_elem(elem_arbre *rac)
{
    elem_arbre *noeud,*noeud2;
    pile *k;
    int stop=0;
    int nbr_occur;
    char chem[100];
    char nom[10];
    char nom2[10];
    char chem2[100];
    liste_rep *lrep=NULL;

    pile *ppp=(pile*)malloc(sizeof(pile));

    chemin *first=NULL,*last,*elem,*ptr,*rrr;
    ppp->elm=NULL;
    ppp->bas=NULL;

    printf("\n");
    afficher_itter(*rac,lrep);
    printf("\n");

    printf("\nDonnez le chemin de l'%cl%cment %c partir duquel vous voulez v%crifier \nl'existence de votre %cl%cment : \n",130,130,133,130,130,130);
    gets(chem);
    strcpy(chem2,chem);

    noeud=chercher_elem(chem,rac);
    if(noeud==NULL)
    {
        printf("Ce chemin est erron%c !!",130);
        getch();
    }
    else
    {
        if(noeud->type=='f')
        {
            printf("\nCeci est le chemin d'un fichier et non pas d'un volume ou r%cpertoire ou \nvotre poste principal !!",130);
            getch();
        }
        else
        {
            if(noeud->fils==NULL)
            {
                if(noeud->type=='v')
                    printf("\nCe volume est vide !! ");
                else
                    printf("\nCe r%cpertoire est vide !! ",130);

                getch();
            }
            else
            {
                printf("\nDonnez le nom de l'%cl%cment %c chercher : ",130,130,133);
                gets(nom);

                if(strcmp(nom,rac->nom)==0)
                {
                    printf("Veuillez choisir un nom autre que celui de vote disque SVP !!");
                }
                else
                {
                    nbr_occur=nbr_elem(rac,nom);
                    if(nbr_occur==0)
                    {
                        printf("\nCet %cl%cment n'existe pas !!",130,130);
                        getch();
                    }
                    else
                    {
                        if(nbr_occur==1)
                        {
                            printf("\nCet %cl%cment existe 1 fois dans l'adresse suivante :",130,130);
                        }
                        else
                        {
                            printf("\nCet %cl%cment existe %d fois dans les adresses suivantes :",130,130,nbr_occur);
                        }


                        noeud2=noeud->fils;

                        do
                        {

                            if(strcmp(noeud2->nom,nom)==0)
                            {
                                printf("\n%s\t: %s\\",noeud2->nom,chem2);

                                if(noeud2->fils==NULL)
                                {
                                    ptr=first;
                                    while(ptr!=NULL)
                                    {
                                        printf("%s\\",ptr->contenu);
                                        ptr=ptr->suiv;
                                    }
                                    printf("%s",noeud2->nom);

                                }
                            }

                            if(noeud2->fils!=NULL&&noeud2->frere!=NULL)
                            {
                                ppp=Empiler(ppp,noeud2);
                            }

                            if(noeud2->fils!=NULL)
                            {
                                elem=(chemin*)malloc(sizeof(chemin));
                                strcpy(elem->contenu,noeud2->nom);
                                elem->suiv=NULL;

                                if(first==NULL)
                                {
                                    first=elem;
                                    last=elem;
                                }
                                else
                                {
                                    last->suiv=elem;
                                    last=elem;
                                }

                                if(strcmp(noeud2->nom,nom)==0)
                                {
                                    ptr=first;
                                    while(ptr!=NULL)
                                    {
                                        if(ptr->suiv==NULL)
                                            printf("%s",ptr->contenu);
                                        else
                                            printf("%s\\",ptr->contenu);

                                        ptr=ptr->suiv;
                                    }
                                }

                                noeud2=noeud2->fils;
                            }
                            else
                            {
                                if(noeud2->frere!=NULL)
                                {
                                    noeud2=noeud2->frere;
                                }
                                else
                                {
                                    if(EstVide(ppp)!=1)
                                    {
                                        strcpy(nom2,ppp->elm->nom);
                                        noeud2=ppp->elm->frere;
                                        k=ppp;
                                        ppp=ppp->bas;
                                        free(k);
                                    }
                                    else
                                    {
                                        k=ppp;
                                        ppp=ppp->bas;
                                        free(k);
                                        stop=1;
                                    }

                                    if(first!=NULL&&stop!=1)
                                    {
                                        if(first==last)
                                        {
                                            first=NULL;
                                            last=NULL;
                                            free(ptr);
                                        }
                                        else
                                        {
                                            ptr=first;

                                            if(strcmp(ptr->contenu,nom2)==0)
                                            {
                                                while(ptr!=NULL)
                                                {
                                                    rrr=ptr;
                                                    ptr=ptr->suiv;
                                                    free(rrr);
                                                }

                                                first=NULL;
                                                last=NULL;
                                            }
                                            else
                                            {
                                                while(ptr!=NULL&&strcmp(ptr->suiv->contenu,nom2)!=0)
                                                {
                                                    ptr=ptr->suiv;
                                                }

                                                if(ptr!=NULL)
                                                {
                                                    last=ptr;
                                                    free(ptr->suiv);
                                                    last->suiv=NULL;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        while(stop!=1);

                        printf("\n\nAppuyez sur une touche pour continuer");

                        getch();
                    }
                }
            }

        }
    }

}

void copier_elem(elem_arbre *rac)
{
    elem_arbre *noeud,*noeud3,*p;
    pile *k;
    int stop=0,trouve;
    char chem[100];
    liste_rep *lrep=NULL;
    pile *ppp2=(pile*)malloc(sizeof(pile));
    pile *ppp=(pile*)malloc(sizeof(pile));
    ppp->elm=NULL;
    ppp->bas=NULL;
    ppp2->elm=NULL;
    ppp2->bas=NULL;

    printf("\n");
    afficher_itter(*rac,lrep);
    printf("\n");

    printf("\nDonnez le chemin de l'%cl%cment %c copier  : \n",130,130,133);
    gets(chem);

    noeud=chercher_elem(chem,rac);

    if(noeud==NULL)
    {
        printf("Ce chemin est erron%c !!",130);
        getch();
    }
    else
    {
        if(noeud->type=='d')
        {
            printf("Ceci est le chemin de votre disque et non pas d'un Fichier ou R%cpertoire ou Volume !!",130);
            getch();
        }
        else
        {
            printf("\nDonnez le chemin d'un volume ou r%cpertoire dans lequel vous voulez \ncopier l'%cl%cment : \n",130,130,130);
            gets(chem);

            noeud3=chercher_elem(chem,rac);
            if(noeud3==NULL)
            {
                printf("Ce chemin est erron%c !!",130);
                getch();
            }
            else
            {
                if(noeud3->type=='f')
                {
                    printf("Il est impossible de faire la copie car c'est le chemin d'un fichier !!",136);
                    getch();

                }
                else
                {

                    if(noeud3==noeud)
                    {
                        printf("Il est impossible de faire la copie car c'est le m%cme chemin !!",136);
                        getch();
                    }
                    else
                    {
                        if((noeud->type=='r'||noeud->type=='v')&&noeud->fils!=NULL&&existence_d_un_elem_ds_un_volrprt(noeud,noeud3)==1)//on cherche le quoi à copier dans le ou emplacement
                        {
                            printf("Il est impossible de copier un contenu principal dans son sous contenu !!");
                            getch();
                        }
                        else
                        {
                            trouve=0;

                            for(p=noeud3->fils; p!=NULL&&strcmp(p->nom,noeud->nom)!=0; p=p->frere);

                            if(p!=NULL)
                                trouve=1;


                            if(trouve==1)
                            {
                                printf("Il est impossible de faire la copie car dans cet emplacement il existe \nun %cl%cment qui porte le m%cme nom que celui %c copier !!",130,130,136,133);
                                getch();
                            }
                            else
                            {
                                if(noeud3->fils==NULL)
                                {
                                    noeud3->fils=(elem_arbre*)malloc(sizeof(elem_arbre));
                                    strcpy(noeud3->fils->nom,noeud->nom);
                                    noeud3->fils->frere=NULL;
                                    noeud3->fils->fils=NULL;
                                    noeud3->fils->type=noeud->type;
                                    noeud3=noeud3->fils;
                                }
                                else
                                {
                                    noeud3=noeud3->fils;

                                    while(noeud3->frere!=NULL)
                                    {
                                        noeud3=noeud3->frere;
                                    }

                                    noeud3->frere=(elem_arbre*)malloc(sizeof(elem_arbre));
                                    strcpy(noeud3->frere->nom,noeud->nom);
                                    noeud3->frere->frere=NULL;
                                    noeud3->frere->fils=NULL;
                                    noeud3->frere->type=noeud->type;
                                    noeud3=noeud3->frere;
                                }

                                if(noeud->type=='r'&&noeud->fils!=NULL)
                                {

                                    noeud=noeud->fils;
                                    noeud3->fils=(elem_arbre*)malloc(sizeof(elem_arbre));
                                    strcpy(noeud3->fils->nom,noeud->nom);
                                    noeud3->fils->frere=NULL;
                                    noeud3->fils->fils=NULL;
                                    noeud3->fils->type=noeud->type;
                                    noeud3=noeud3->fils;

                                    do
                                    {
                                        if(noeud->fils!=NULL&&noeud->frere!=NULL)
                                        {
                                            ppp=Empiler(ppp,noeud);
                                            ppp2=Empiler(ppp2,noeud3);
                                        }

                                        if(noeud->fils!=NULL)
                                        {
                                            noeud=noeud->fils;
                                            p=(elem_arbre*)malloc(sizeof(elem_arbre));
                                            strcpy(p->nom,noeud->nom);
                                            p->frere=NULL;
                                            p->fils=NULL;
                                            p->type=noeud->type;
                                            noeud3->fils=p;
                                            noeud3->frere=NULL;
                                            noeud3=noeud3->fils;

                                        }
                                        else
                                        {
                                            if(noeud->frere!=NULL)
                                            {
                                                noeud=noeud->frere;
                                                p=(elem_arbre*)malloc(sizeof(elem_arbre));
                                                strcpy(p->nom,noeud->nom);
                                                p->frere=NULL;
                                                p->fils=NULL;
                                                p->type=noeud->type;
                                                noeud3->frere=p;
                                                noeud3->fils=NULL;
                                                noeud3=noeud3->frere;
                                            }
                                            else
                                            {
                                                if(EstVide(ppp)!=1)
                                                {
                                                    noeud=ppp->elm->frere;
                                                    noeud3=ppp2->elm;

                                                    p=(elem_arbre*)malloc(sizeof(elem_arbre));
                                                    strcpy(p->nom,ppp->elm->frere->nom);
                                                    p->frere=NULL;
                                                    p->fils=NULL;
                                                    p->type=ppp->elm->type;
                                                    noeud3->frere=p;
                                                    noeud3=noeud3->frere;

                                                    k=ppp;

                                                    ppp=ppp->bas;

                                                    free(k);
                                                    k=ppp2;
                                                    ppp2=ppp2->bas;
                                                    free(k);
                                                }
                                                else
                                                {
                                                    k=ppp;
                                                    ppp=ppp->bas;
                                                    free(k);
                                                    k=ppp2;
                                                    ppp2=ppp2->bas;
                                                    free(k);
                                                    stop=1;
                                                }
                                            }
                                        }
                                    }
                                    while(stop!=1);
                                }

                                printf("Votre %cl%cment a %ct%c copi%c avec succ%cs !!",130,130,130,130,130,138);

                                printf("\n");
                                afficher_itter(*rac,lrep);
                                printf("\n");
                                printf("Appuyez sur une touche pour continuer");
                                getch();
                            }
                        }
                    }
                }
            }
        }
    }
}

void deplacer_elem(elem_arbre *rac)
{
    elem_arbre *noeud,*noeud3,*p;
    pile *k;
    int stop=0,trouve;
    char chem[100];
    char chem3[100];
    liste_rep *lrep=NULL;
    pile *ppp2=(pile*)malloc(sizeof(pile));
    pile *ppp=(pile*)malloc(sizeof(pile));
    ppp2->elm=NULL;
    ppp2->bas=NULL;

    ppp->elm=NULL;
    ppp->bas=NULL;

    printf("\n");
    afficher_itter(*rac,lrep);
    printf("\n");

    printf("\nDonnez le chemin de l'%cl%cment %c d%cplacer  : \n",130,130,133,130);
    gets(chem);
    strcpy(chem3,chem);

    noeud=chercher_elem(chem,rac);


    if(noeud==NULL)
    {
        printf("Ce chemin est erron%c !!",130);
        getch();
    }
    else
    {
        if(noeud->type=='d')
        {
            printf("Ceci est le chemin de votre disque et non pas d'un Fichier ou R%cpertoire ou Volume !!",130);
            getch();
        }
        else
        {
            printf("\nDonnez le chemin d'un volume ou r%cpertoire dans lequel vous voulez \nd%cplacer l'%cl%cment : \n",130,130,130,130);
            gets(chem);
            noeud3=chercher_elem(chem,rac);

            if(noeud3==NULL)
            {
                printf("Ce chemin est erron%c !!",130);
                getch();
            }
            else
            {
                if(noeud3->type=='f')
                {
                    printf("Il est impossible de faire le d%cplacement car c'est le chemin d'un fichier !!",130);
                    getch();
                }
                else
                {

                    if(noeud3==noeud)
                    {
                        printf("Il est impossible de faire le d%cplacement car c'est le m%cme chemin !!",130);
                        getch();
                    }
                    else
                    {
                        if((noeud->type=='r'||noeud->type=='v')&&noeud->fils!=NULL&&existence_d_un_elem_ds_un_volrprt(noeud,noeud3)==1)//on cherche le quoi à copier dans le ou emplacement
                        {
                            printf("Il est impossible de d%cplacer un contenu principal dans son sous contenu !!",130);
                            getch();
                        }
                        else
                        {


                            trouve=0;

                            for(p=noeud3->fils; p!=NULL&&strcmp(p->nom,noeud->nom)!=0; p=p->frere);

                            if(p!=NULL)
                                trouve=1;

                            if(trouve==1)
                            {
                                printf("Il est impossible de faire le d%cplacement car dans cet emplacement il existe \nun %cl%cment qui porte le m%cme nom que celui %c d%cplacer !!",130,130,130,136,133,130);
                                getch();
                            }
                            else
                            {


                                if(noeud3->fils==NULL)
                                {
                                    noeud3->fils=(elem_arbre*)malloc(sizeof(elem_arbre));
                                    strcpy(noeud3->fils->nom,noeud->nom);
                                    noeud3->fils->frere=NULL;
                                    noeud3->fils->fils=NULL;
                                    noeud3->fils->type=noeud->type;
                                    noeud3=noeud3->fils;
                                }
                                else
                                {
                                    noeud3=noeud3->fils;

                                    while(noeud3->frere!=NULL)
                                    {
                                        noeud3=noeud3->frere;
                                    }

                                    noeud3->frere=(elem_arbre*)malloc(sizeof(elem_arbre));
                                    strcpy(noeud3->frere->nom,noeud->nom);
                                    noeud3->frere->frere=NULL;
                                    noeud3->frere->fils=NULL;
                                    noeud3->frere->type=noeud->type;
                                    noeud3=noeud3->frere;
                                }

                                if(noeud->type=='r'&&noeud->fils!=NULL)
                                {

                                    noeud=noeud->fils;
                                    noeud3->fils=(elem_arbre*)malloc(sizeof(elem_arbre));
                                    strcpy(noeud3->fils->nom,noeud->nom);
                                    noeud3->fils->frere=NULL;
                                    noeud3->fils->fils=NULL;
                                    noeud3->fils->type=noeud->type;
                                    noeud3=noeud3->fils;

                                    do
                                    {
                                        if(noeud->fils!=NULL&&noeud->frere!=NULL)
                                        {
                                            ppp=Empiler(ppp,noeud);
                                            ppp2=Empiler(ppp2,noeud3);
                                        }

                                        if(noeud->fils!=NULL)
                                        {
                                            noeud=noeud->fils;
                                            p=(elem_arbre*)malloc(sizeof(elem_arbre));
                                            strcpy(p->nom,noeud->nom);
                                            p->frere=NULL;
                                            p->fils=NULL;
                                            p->type=noeud->type;
                                            noeud3->fils=p;
                                            noeud3->frere=NULL;
                                            noeud3=noeud3->fils;

                                        }
                                        else
                                        {
                                            if(noeud->frere!=NULL)
                                            {
                                                noeud=noeud->frere;
                                                p=(elem_arbre*)malloc(sizeof(elem_arbre));
                                                strcpy(p->nom,noeud->nom);
                                                p->frere=NULL;
                                                p->fils=NULL;
                                                p->type=noeud->type;
                                                noeud3->frere=p;
                                                noeud3->fils=NULL;
                                                noeud3=noeud3->frere;
                                            }
                                            else
                                            {
                                                if(EstVide(ppp)!=1)
                                                {
                                                    noeud=ppp->elm->frere;
                                                    noeud3=ppp2->elm;

                                                    p=(elem_arbre*)malloc(sizeof(elem_arbre));
                                                    strcpy(p->nom,ppp->elm->frere->nom);
                                                    p->frere=NULL;
                                                    p->fils=NULL;
                                                    p->type=ppp->elm->type;
                                                    noeud3->frere=p;
                                                    noeud3=noeud3->frere;

                                                    k=ppp;

                                                    ppp=ppp->bas;

                                                    free(k);
                                                    k=ppp2;
                                                    ppp2=ppp2->bas;
                                                    free(k);
                                                }
                                                else
                                                {
                                                    k=ppp;
                                                    ppp=ppp->bas;
                                                    free(k);
                                                    k=ppp2;
                                                    ppp2=ppp2->bas;
                                                    free(k);
                                                    stop=1;
                                                }
                                            }
                                        }
                                    }
                                    while(stop!=1);
                                }

                                supprimer_elem_couper(rac,chem3);
                                printf("Votre %cl%cment a %ct%c d%cplac%c avec succ%cs !!",130,130,130,130,130,130,138);
                                printf("\n");
                                afficher_itter(*rac,lrep);
                                printf("\n");
                                printf("\nAppuyez sur une touche pour continuer");
                                getch();
                            }
                        }
                    }
                }
            }
        }
    }

}

void renommer(elem_arbre *rac)
{
    char chem[100],nom[10];
    elem_arbre*noeud;
    int repeter;
    liste_rep *lrep=NULL;

    printf("\n");
    afficher_itter(*rac,lrep);
    printf("\n");
    printf("\nDonnez le chemin de l'%cl%cment que vous voulez renommer : \n",130,130);
    gets(chem);

    noeud=chercher_elem(chem,rac);


    if(noeud==NULL)
    {
        printf("Ce chemin est erron%c !!",130);
        getch();
    }
    else
    {
        do
        {
            printf("Donnez le nouveau nom : ");
            gets(nom);
            repeter=redandonce_nom(rac,noeud,nom);
            if(repeter==1)
                printf("Il vaut mieux changer de nom SVP !!");
        }
        while(strcmp(nom,"\0")==0||repeter==1);

        strcpy(noeud->nom,nom);

        printf("Modificatoin r%cussie !!",130);

        printf("\n");
        afficher_itter(*rac,lrep);
        printf("\n");

        printf("\nAppuyez sur une touche pour continuer");
        getch();

    }

}

void titre(void)
{
    printf("                         -------------------------------------------------------\n");
    printf("                        |                   ~~ ARBO-GV ~~                       |\n");
    printf("                        |    PROGRAMME D'ARBORESCENCE ET GESTION DES VOLUMES    |\n");
    printf("                         -------------------------------------------------------\n");
}

void introduction(void)
{
    printf("\n\n\n\t\t\t\t       Salutation (^_^) !!\n\t Voici un programme de gestion des volumes qui permet d'afficher et de g%crer votre disque \n                                  de la mani%cre dont vous voulez\n ",130,138);
    printf("\t                 Appuyez sur n'importe quelle touche pour commencer ");

    getch();
}

int menu_prin(elem_arbre rac)
{
    int boucle=1,rep;

    clrscr();

    titre();


    printf(" \n                                 --------------------------------------\n");
    printf("                                |           MENU PRINCIPAL             |\n");
    printf("                                 --------------------------------------\n");
    printf("                                |   1 . Ajouter un volume              |\n");;
    printf("                                |   2 . G%crer votre disque             |\n",130);
    printf("                                |   3 . Afficher la liste des volumes  |\n",130);
    printf("                                |   4 . Quitter                        |\n");
    printf("                                 --------------------------------------\n");
    do
    {
        printf("\t\t\t\t\t\t    Votre Choix : ");
        rep=getch();


        if(rep!=49&&rep!=50&&rep!=51&&rep!=52)
        {
            printf("\nVeuillez effectuer un choix entre 1 et 4 !!\n");
            boucle=1;
        }
        else
        {
            if(rac.fils!=NULL)
            {
                boucle=0;
            }
            else
            {
                if(rep==50||rep==51)
                    printf("\nVous devez ajouter au moins un volume d'abord !!\n",130);
                else
                    boucle=0;
            }
        }
    }
    while(boucle==1);



    return rep;
}

int menu_gest_disque(void)
{
    int rep;

    clrscr();

    titre();

    printf(" \n                            -------------------------------------------------\n");
    printf("                           |                GESTION DU DISQUE                |\n");
    printf("                            -------------------------------------------------\n");
    printf("                           |   1 . Ajouter un nouveau %cl%cment (R/F)          |\n",130,130);
    printf("                           |   2 . Afficher le contenu d'un %cl%cment (V/R)    |\n",130,130);
    printf("                           |   3 . Copier un %cl%cment (V/R/F)                 |\n",130,130);
    printf("                           |   4 . D%cplacer un %cl%cment (V/R/F)               |\n",130,130,130);
    printf("                           |   5 . Renommer un %cl%cment (D/V/R/F)             |\n",130,130);
    printf("                           |   6 . Supprimer un %cl%cment (D/V/R/F)            |\n",130,130);
    printf("                           |   7 . Nombre d'occurence d'un %cl%cment (V/R/F)   |\n",130,130);
    printf("                            -------------------------------------------------\n");

    printf("\nR : retourner au menu principal\n");
    printf("Votre Choix : ");

    do
    {
        rep=getch();
    }
    while(rep!=49&&rep!=50&&rep!=51&&rep!=52&&rep!=53&&rep!=54&&rep!=55&&rep!=114&&rep!=82);

    return rep;
}

int main()
{
    elem_arbre *rac;
    liste_rep *lrep=NULL;
    int choix1=-1,choix2;

    titre();
    introduction();
    rac=initialiser(rac);

    do
    {
        switch (choix1)
        {
        case -1 :
            choix1=menu_prin(*rac);
            break;

        case 49 :
            ajouter_vol(rac);
            choix1=-1;
            break;
        case 51 :
            printf("\n");
            afficher_itter(*rac,lrep);
            contenu_disque(rac);
            printf("\n\nAppuyez sur n'importe quelle touche pour continuer ");
            getch();
            choix1=-1;
            break;
        case 50 :
        {
            choix2=menu_gest_disque();
            switch (choix2)
            {
            case 49 :
                ajouter_nv_elem(rac);
                choix1=50;
                break;
            case 50 :
                contenu_reprt_volume(rac);
                choix1=50;
                break;
            case 51 :
                copier_elem(rac);
                choix1=50;
                break;
            case 52 :
                deplacer_elem(rac);
                choix1=50;
                break;
            case 53 :
                renommer(rac);
                choix1=50;
                break;
            case 54 :
                supprimer_elem(rac);
                if(rac->fils==NULL)
                    choix1=-1;
                else
                    choix1=50;
                break;
            case 55 :
                nbr_occur_elem(rac);
                choix1=50;
                break;
            case 82 :
                choix1=-1;
                break;
            case 114:
                choix1=-1;
                break;

            }
        }
        }
    }
    while(choix1!=52);

    printf("\n\n\t\t      Merci pour avoir utilis%c ce programme (^_^) %c tr%cs bient%ct !!\n\n",130,133,138,147);
    getch();

    return 0;
}
