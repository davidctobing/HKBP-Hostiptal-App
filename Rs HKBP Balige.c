/*
David 	 : 13318038
Melani	: 13318059
Yolanda	:13318001
*/

#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<process.h> 
#include<stdlib.h> /*sebuah libaray disitulah printf scanf*/
#include<dos.h> /*case 2*/
/*
r	Membaca file sesuai namafilenya untuk dibaca, jika file tidak ada maka akan bernilai NULL.
w	Membuka file untuk ditulis, jika sebelumnya sudah ada nama file yang sama, maka akan dilakukan overwrite/menimpa file dengan yang baru.
a	Membuka file sesuai namafilenya untuk ditambahkan datanya dipaling bawah baris terakhir. Jika file tidak ada, maka akan membuat file baru secara otomatis.
r+	Sama dengan “r” tetapi selain file dapat dibaca juga dapat di tulis
w+	Sama dengan “w” tetapi selain file dapat ditulis juga dapat dibaca
a+	Sama dengan ”a” tetapi selain file dapat ditulis file juga dapat dibaca*/

struct contact /*sama seperti array tetapi bisa beberapa tipe data*/
{
    long ph;
    char name[20],add[20],umur[30];
} list;
char query[20],name[20];
FILE *fp, *ft;
int i,n,ch,l,found;
int main()
{
main:
    /* ************Menu ***********************  */
    /*cls untuk menghapus compiller sebelumnya*/
    system("cls");   
    printf("\n\t +++ Welcome to HKBP Hospital Balige +++");
    printf("\n\n\n\t\t\tMAIN MENU\n\t\t=====================\n\t\t[1] Tambahkan Pasien\n\t\t[2] Daftar Pasien\n\t\t[3] Cari Pasien\n\t\t[4] Edit data Pasien\n\t\t[5] Hapus Pasien\n\t\t[0] Exit\n\t\t=================\n\t\t");
    printf("Pilih Salah satu:");
    scanf("%d",&ch);
    switch(ch)
    {
    case 0:
        printf("\n\n\t\tApakah anda ingin kembali?");
        break;
        /* *********************Menambah pasien************  */
    case 1:
        system("cls"); /*menghapus compiller sebelumnya*/
        fp=fopen("contact.txt","a");
        for (;;)
        {
            fflush(stdin);
            printf("Untk kembali tekan spasi & enter di kolom yang kosong\n Nama :");
            scanf("%[^\n]",&list.name);
            if(stricmp(list.name,"")==0 || stricmp(list.name," ")==0)
                break;
            fflush(stdin); /** menghapus isi dari input buffer**/
            printf("Nomor Kamar:");
            scanf("%ld",&list.ph);
            fflush(stdin);
            printf("Lama Dirawat:");
            scanf("%[^\n]",&list.add);
            fflush(stdin); 
            printf("Umur Pasien:");
            gets(list.umur);
            printf("\n");
			fwrite(&list,sizeof(list),1,fp);
        }
        fclose(fp);
        break;
        
        /* *********************daftar pasien*************************  */

    case 2:
        system("cls");
        printf("\n\t\t================================\n\t\t\tDAFTAR PASIEN\n\t\t================================\n\nName\t\tkamar No\t    Lama dirawat\t\tUmur.\n=================================================================\n\n");
        for(i=97; i<=122; i=i+1)
        {
            fp=fopen("contact.dll","r");
            fflush(stdin);
            found=0;
            while(fread(&list,sizeof(list),1,fp)==1)
            {
                if(list.name[0]==i || list.name[0]==i-32)
                {
                    printf("\nName \t: %s\nKamar \t: %ld\n Hari \t: %s\nUmur\t: %s\n",list.name,list.ph,list.add,list.umur);
                    found++;
                }
            }
            if(found!=0)
            {
                printf("=========================================================== [%c]-(%d)\n\n",i-32,found);
                getch();
            }
            fclose(fp);
        }
        break;
        
        
        /* *******************Mencari pasien**********************  */

    case 3:

        system("cls");

        do
        {
        	
            found=0;
            printf("\n\n\t..::CARI PASIEN\n\t===========================\n\t..::Nama pasien yang ingin dicari: ");
            fflush(stdin);
            scanf("%[^\n]",&query);
            l=strlen(query);
            fp=fopen("contact.dll","r");
            system("cls");
            printf("\n\n..::Hasil pencarian '%s' \n===================================================\n",query);
            while(fread(&list,sizeof(list),1,fp)==1)

            {
                for(i=0; i<=l; i++)
                    name[i]=list.name[i];
                name[l]='\0';
                if(stricmp(name,query)==0)
                {
                    printf("\n..::Nama\t: %s\n..::Kamar\t: %ld\n..::Hari\t: %s\n..::Umur\t: %s\n",list.name,list.ph,list.add,list.umur);
                    found++;
                    if (found%4==0)
                    {
                        printf("..::Press any key to continue...");
                        getch();

                    }

                }

            }

            if(found==0)
                printf("\n..::Tidak dapat ditemukan!");
            else
                printf("\n..::%d match(s) found!",found);
            fclose(fp);
            printf("\n ..::Try again?\n\n\t[1] Yes\t\t[0] No\n\t");
            scanf("%d",&ch);
        }
        while(ch==1);
        break;

        /* *********************edit pasien************************/

    case 4:
        system("cls");
        fp=fopen("contact.dll","r");
        ft=fopen("temp.dat","w");
        fflush(stdin);
        printf("..::Edit contact\n===============================\n\n\t..::Masukkan nama yang akan di edit:");
        scanf("%[^\n]",name);
        while(fread(&list,sizeof(list),1,fp)==1)

        {
            if(stricmp(name,list.name)!=0)
                fwrite(&list,sizeof(list),1,ft);

        }

        fflush(stdin);
        printf("\n\n..::Editing '%s'\n\n",name);
        printf("..::Nama:");
        scanf("%[^\n]",&list.name);
        fflush(stdin);
        printf("..::Kamar:");
        scanf("%ld",&list.ph);
        fflush(stdin);
        printf("..::Lama di rawat:");
        scanf("%[^\n]",&list.add);
        fflush(stdin);
        printf("..::umur:");
        gets(list.umur);
        printf("\n");
        fwrite(&list,sizeof(list),1,ft);
        fclose(fp);
        fclose(ft);
        
        remove("contact.dll");
        rename("temp.dat","contact.dll");
        break;

        /* ********************delete contacts**********************/

    case 5:
        system("cls");
        fflush(stdin);
        printf("\n\n\t..::Menghapus Pasien\n\t==========================\n\t..::Masukkan nama pasien yang akan di hapus:");
        scanf("%[^\n]",&name);
        fp=fopen("contact.dll","r");
        ft=fopen("temp.dat","w");
        while(fread(&list,sizeof(list),1,fp)!=0)
            if (stricmp(name,list.name)!=0)
                fwrite(&list,sizeof(list),1,ft);
        fclose(fp);
        fclose(ft);
        remove("contact.dll");
        rename("temp.dat","contact.dll");
        break;

    default:
        printf("Invalid choice");
        break;

    }
    printf("\n\n\n..::pilih:\n\n\t[1] Kembali ke menu\t\t[0] Exit\n");
    scanf("%d",&ch);
    
    
    switch (ch)
    {
    case 1:
        goto main;
    case 0:
        break;
    default:
        printf("Invalid choice");
        break;
    }

    return 0;

}
