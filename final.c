#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
struct plant
{
  int pid, ptemp;
  char pname[30];
  char scpname[50], stype[20], sunavail[20], pdesc[100];
  float pcycle, pwater;
};
int count = 0;
FILE *fp;

    //functions prototyping 1.ADMIN PART
void adminmenu ();
void admwrite ();
void addisp ();
void admdel ();
void input (struct plant *s);
void display (struct plant st);
    // 2.USER PART
char *getsoil (struct plant *p);
char *getsun (struct plant *p);
int *gettemp (struct plant p);
void userwelcomescreen ();
void criteriamenu ();		//for criteria
void display_sp (int n1, char a2[20], char a3[20]);
    //function defination 1.ADMIN PART
void
adminmenu ()
{
  system ("cls");
  int ch2;
  printf
    ("--------------------------------------------------------------------------------\n");
  printf
    ("1.ADD PLANT---------------------------------------------------------------------\n");
  printf
    ("2.DISPLAY ALL PLANTS------------------------------------------------------------\n");
  printf
    ("3.DELETE A PLANT----------------------------------------------------------------\n");
  printf
    ("4.Back To Main Menu-------------------------------------------------------------\n");
  printf
    ("--------------------------------------------------------------------------------\n");
  scanf ("Enter Your Choice :\n");
  scanf ("%d", &ch2);
  switch (ch2)
    {
    case 1:
      admwrite ();
      break;
    case 2:
      addisp ();
      break;
    case 3:
      admdel ();
      break;
    case 4:
      main ();
    default:
      printf ("Please try again with correct input option. Thank You \n");
      adminmenu ();
    }
}

void
input (struct plant *s)
{
  printf ("\n ENTER PLANT RECORDS : \n ");
  printf ("\n Enter Plant Id  \n ");
  scanf ("%d", &s->pid);
  fflush (stdin);
  printf ("\n Enter Plant Name  \n ");
  gets (s->pname);
  printf ("\n Enter Plant Scientific Name \n ");
  gets (s->scpname);
  printf
    ("\n Enter soil type(enter only from these [Sandy Soil] [Loamy Soil] [Clay Soil]) \n ");
  printf ("Please enter a space after writing the soil type... \n ");
  gets (s->stype);
  s->stype[strlen (s->stype) - 1] = '\0';
  fflush (stdin);
  printf
    ("\n Enter sun status enter only from these [Full sunlight] ,[Semi/shaded]) \n ");
  printf ("Please enter a space after writing the soil type... \n ");
  gets (s->sunavail);
  s->sunavail[strlen (s->sunavail) - 1] = '\0';
  fflush (stdin);
  printf ("\n Enter plant description \n ");
  gets (s->pdesc);
  printf ("\n Enter growing temperature range requirement : \n");
  printf ("[1->(15-25 degree celsius)] \n");
  printf ("[2->(25-35 degree celsius)] \n");
  printf ("[3->(35-45 degree celsius)] \n");
  printf ("\n Enter Number\n ");
  scanf ("%d", &s->ptemp);
  printf ("\n Enter plant life cycle in months \n ");
  fflush (stdout);
  scanf ("%f", &s->pcycle);
  printf ("\n Enter growing water requirement per day / litres \n ");
  scanf ("%f", &s->pwater);
  printf ("\n---------------------------------------------- \n");

}

void
admwrite ()
{
  system ("cls");
  struct plant data;
  fp = fopen ("plant.dat", "ab+");
  input (&data);
  fwrite (&data, sizeof (data), 1, fp);

  printf ("Process completed ...... Record Added\n");
  fclose (fp);
  int ch1;
  printf ("Enter 1 to continue adding or else any key to go to the menu \n");
  scanf ("%d", &ch1);
  if (ch1 == 1)
    admwrite ();
  else
    adminmenu ();

}

void
display (struct plant st)
{

  printf ("================================================");
  printf ("\n Plant Id  : %d", st.pid);
  printf ("\n-------------------------------------------");
  printf ("\n Plant Name : %s  ", st.pname);
  printf ("\n-------------------------------------------");
  printf ("\n Plant Scientific Name : %s  ", st.scpname);
  printf ("\n-------------------------------------------");
  printf ("\n Soil type : %s ", st.stype);
  printf ("\n-------------------------------------------");
  printf ("\n Sun Status : %s ", st.sunavail);
  printf ("\n-------------------------------------------");
  printf ("\n Plant description : %s ", st.pdesc);
  printf ("\n-------------------------------------------");
  printf ("\n Growing temperature range requirement : \n");
  if (st.ptemp == 1)
    {
      printf (" 15-25 degree celcius\n");
    }
  else if (st.ptemp == 2)
    {
      printf (" 25-35 degree celcius\n");
    }
  else if (st.ptemp == 3)
    {
      printf (" 35-45 degree celcius\n");
    }
  printf ("\n-------------------------------------------");
  fflush (stdout);
  printf ("\n Plant life cycle in months : %f ", st.pcycle);
  printf ("\n-------------------------------------------");
  printf ("\n Growing water requirement : %f in Litre", st.pwater);
  printf ("\n");
  fflush (stdout);
  printf ("===============================================");
}

void
addisp ()
{
  system ("cls");
  struct plant data;


  printf ("\n\nDISPLAYING ALL RECORD !!!\n");
  fp = fopen ("plant.dat", "rb");
  if (fp == NULL)
    {
      printf ("File cannot open");
      exit (0);
    }

  while ((fread (&data, sizeof (data), 1, fp)) > 0)
    {
      display (data);

    }
  fclose (fp);

  fclose (fp);
  int cho;
  printf ("\n Enter 1 to go back \n");
  scanf ("%d", &cho);
  if (cho == 1)
    adminmenu ();
}

void
admdel ()
{
  system ("cls");
  int no;
  struct plant data;
  FILE *fd;
  printf ("\n\nDelete Record");
  printf ("\nPlease Enter The plant Id you want to delete: ");
  scanf ("%d", &no);
  fp = fopen ("plant.dat", "rb");
  fd = fopen ("temp.dat", "wb");
  rewind (fp);
  while ((fread (&data, sizeof (data), 1, fp)) > 0)
    {
      if (data.pid != no)
	{
	  fwrite (&data, sizeof (data), 1, fd);
	}
    }
  fclose (fd);
  fclose (fp);
  remove ("plant.dat");
  rename ("temp.dat", "plant.dat");
  printf ("\nRecord deleted.");
  printf ("\n");
  printf ("enter any value...");
  getch ();
  adminmenu ();
}

//function defination 2.USER PART
char *
getsoil (struct plant *p)
{
  return p->stype;
}

char *
getsun (struct plant *p)
{
  return p->sunavail;
}

int *
gettemp (struct plant p)
{
  return p.ptemp;
}

void
userwelcomescreen ()
{
  system ("cls");
  for (int i = 0; i <= 35; i++)
    {
      printf ("*");
    }
  printf ("\n");
  printf ("\n");
  printf ("Welcome to user's urban garden patch  \n");
  printf ("\n");
  for (int j = 0; j <= 35; j++)
    {
      printf ("*");
    }
  printf ("\n");
  printf ("Press any key to move ahead \n");
  getch ();
  criteriamenu ();

}

void
criteriamenu ()
{
  system ("cls");
  int n;
  printf
    ("------------------------------------------------------------------------------");
  printf ("\n\t\t\tSelect Range of Avg Temperature of your Locality");	//first criteria
  printf ("\n\t\t\t\t1. 15-25 degree celsius");
  printf ("\n\t\t\t\t2. 25-35 degree celsius");
  printf ("\n\t\t\t\t3. 35-45 degree celsius");
  printf
    ("\n----------------------------------------------------------------------------");
  printf ("\n\t\t\t\ Please enter number:-");
  scanf ("%d", &n);
  if (n > 3 || n < 1)
    {
      printf ("Please enter proper number");
      criteriamenu ();
    }

  fflush (stdin);


  system ("cls");
  char b2[20];
  printf
    ("\n-----------------------------------------------------------------------------");
  printf ("\n\t\tSelect type of Soil Availability at the planting location");	//second criteria
  printf ("\n 1.Loamy Soil");
  printf ("\n 2.Clay Soil");
  printf ("\n 3.Sandy Soil");
  printf ("\n\t\t\t -> Enter the Soil Type:- ");
  fgets (b2, 15, stdin);
  b2[strlen (b2) - 1] = '\0';
  puts (b2);

  fflush (stdin);
  system ("cls");
  char b3[20];
  printf
    ("\n---------------------------------------------------------------------------\n");
  printf ("Enter Sunlight Conditions at Planting Location\n");	//third criteria
  printf ("Full sunlight\n");
  printf ("Semi/shaded\n");
  printf ("\n\t\t -> Enter Sun Availibilty Status:- ");
  fgets (b3, 15, stdin);
  b3[strlen (b3) - 1] = '\0';
  puts (b3);

  printf
    ("To search according to preference from the database press a key\n");
  display_sp (n, b2, b3);
  getch ();
  printf ("\n");
  printf ("\n");

}

void
display_sp (int n1, char a2[20], char a3[20])
{
  system ("cls");
  printf ("\n");
  printf ("\n");
  struct plant data;
  char *a;
  a = getsoil (&data);
  printf ("%s", a);
  char *b;
  b = getsun (&data);
  printf
    ("You Have These Plants that you can plant according to your criteria  \n");
  printf ("\n");
  printf ("\n");
  printf ("\n");
  int f = 0;
  printf ("----------------------------------------------------\n");
  fp = fopen ("plant.dat", "rb");
  while ((fread (&data, sizeof (data), 1, fp)) > 0)
    {
      if (data.ptemp == n1)
	{
	  if (strcmpi (a, a2) == 0)
	    {
	      if (strcmpi (b, a3) == 0)
		{
		  display (data);
		  f++;
		}
	    }
	}
    }

  printf ("\n");
  printf ("\n");
  fclose (fp);
  if (f == 0)
    printf ("\nRecord does not exist");
  printf ("\n YOUR TOTAL CHOICES ARE: %d", f);
  printf
    ("\nEnter 1 value to go back to the main menu or any number to see the options again");
  getch ();
  int i;
  scanf ("%d", &i);
  if (i == 1)
    {
      main ();
    }
  else
    criteriamenu ();
}

int
main ()
{
  system ("cls");
  int ch1;
  printf
    ("------------------------------------------------------------------------------- \n");
  printf
    ("---------------------------PLANT MANAGEMENT SYSTEM----------------------------- \n");
  printf
    ("1.USER------------------------------------------------------------------------- \n");
  printf
    ("2.ADMIN(Database Manager)------------------------------------------------------ \n");
  printf
    ("3.EXIT------------------------------------------------------------------------- \n");
  printf
    ("------------------------------------------------------------------------------- \n");
  printf ("Enter your Choice :  ");
  scanf ("%d", &ch1);

  switch (ch1)
    {
    case 1:
      userwelcomescreen ();
      break;

    case 2:
      adminmenu ();
      break;

    case 3:
      exit (0);

    default:
      printf ("Please try again with correct input option. Thank You \n");
      main ();
      break;
    }
  return 0;
}
