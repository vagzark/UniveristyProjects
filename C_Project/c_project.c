#include <stdio.h>
#include <stdlib.h>

#define N 100
//dimensions of arrays
struct coordinates{
    int row;
    int coll;
};

int choices(void); //choices menu

void create_array(double ***array,int array_num,struct coordinates array1[N]); //array creation

void print_array1(double ***array,struct coordinates array1[N],int num_choice); //for printing one array

void create_vector(double **vector,int vector_num,int vector_dim[N]); //vector creation

void print_vector1(double **vector,int vector_dim[N],int vector_choice); //for printing one vector

void print_arrayall(double ***array, int array_num,struct coordinates array1[N],int deleted_arrays[N]); //for printing all arrays stored

void print_vectorall(double **vector,int vector_dim[N],int vector_num,int deleted_vectors[N]); //for printing all vectors stored

void prod_array(double ***array,struct coordinates array1[N], int ar1_choice, int ar2_choice);//matrix multiplication

void sum_array(double ***array,struct coordinates array1[N], int ar1_choice, int ar2_choice);//matrix addition

void sub_array(double ***array,struct coordinates array1[N], int ar1_choice, int ar2_choice);//matrix subtraction

void sum_vector(double **vector,int vector_dim[N], int v1_choice, int v2_choice );//vector addition

void sub_vector(double **vector,int vector_dim[N], int v1_choice, int v2_choice );//vector subtraction

void dprod_vector(double **vector,int vector_dim[N], int v1_choice, int v2_choice );//vector dot product

void xprod_vector(double **vector,int vector_dim[N], int v1_choice, int v2_choice );//vector cross product

int delete_arrays(int deleted_arrays[N], int *cnt_deleted_arrays,int delete_choice);//for array deletion

int delete_vectors(int deleted_vectors[N], int *cnt_deleted_vectors,int delete_choice);//for vector deletion


int main(void)
{
    int choice; //users choice of catalogue
    double **array[N]; //3 dimensional array for storing the arrays
    int array_num=0; //count for arrays stored
    struct coordinates array1[N]; //array for storing the dimensions of the arrays stored
    int num_choice; //for choosing which array the user wants to print
    double *vector[N]; //for storing the vectors that the user inputs
    int vector_dim[N]; //for the dimensions of the vectors
    int vector_num=0; //number of vectors
    int vector_choice; //for the vector that the user wants to print
    int print_choice; //for the users choice about printing one or all vectors/arrays
    int opperation1_choice, opperation2_choice; //for storing the operation the user wants to execute
    int ar1_choice, ar2_choice;//arrays that have been chosen for operations
    int v1_choice, v2_choice;//vectors that have been chosen for operations
    
    
    int deleted_arrays[N]; //for storing the deleted arrays
    int cnt_deleted_arrays=0; //for storing the number of arrays that have been deleted
    int delete_choice; //for storing the arrays number that the user want to delete
    
    int deleted_vectors[N]; //for storing the vectors that have been deleted
    int cnt_deleted_vectors=0; //for storing how many vectors have been deleted
    
    int i,j,k;


    while(1)
    {
        choice=choices(); //catalogue choice of the user

        switch(choice)
        {
            case 1: //array creation
                create_array(array,array_num,array1);
                array_num++;
                break;

            case 2: //vector creation
                create_vector(vector,vector_num,vector_dim);
                vector_num++;
                break;
            case 3:
                
                printf("nChoices:\n");
                printf("1.Printing of specific array.");
                printf("\n2.Printing of all available arrays");
                printf("\n-> ");
                scanf("%d",&print_choice);
                while(print_choice<0 || print_choice>2)
                {
                    printf("\nPlease choose one of the available choices!\n");
                    printf("-> ");
                    scanf("%d",&print_choice);
                }
                if(print_choice==1)
                {
                    printf("\nWhich array would you like to print?\n");
                    printf("-> ");
                    scanf("%d",&num_choice);
                    printf("\n");
                    while(num_choice>array_num || num_choice<1)
                    {
                        printf("\nThis array does not exist!");
                        printf("\nPlease repeat the input of the table number you would like to print:");
                        printf("\n-> ");
                        scanf("%d",&num_choice);
                    };
                    j=0; //check if the array is already deleted
                    for(i=0; i<=cnt_deleted_arrays; i++)
                    {
                        if(deleted_arrays[i]==num_choice)
                        {
                            printf("\nThis array has been deleated!\n");
                            j++;
                        }
                    }
                    if(j==0)
                    {
                        print_array1(array,array1,num_choice);
                        break;
                    }
                    else
                        break;
                }
                else{
                    printf("\n");
                    print_arrayall(array,array_num,array1,deleted_arrays);
                    break;
                }
            case 4:
                printf("\nChoices:\n");
                printf("1.Printing of a specific vector.");
                printf("\n2.Printing of all available vectors.");
                printf("\n-> ");
                scanf("%d",&print_choice);
                while(print_choice<1 || print_choice>2)
                {
                    printf("\nPlease choose one of the available vectors!\n");
                    printf("-> ");
                    scanf("%d",&print_choice);
                }
                if(print_choice==1)
                {
                    printf("\nWhich vector would you like to print?\n");
                    printf("-> ");
                    scanf("%d",&vector_choice);
                    while(vector_choice>vector_num || vector_choice<1)
                    {
                        printf("\nThis vector does not exist!");
                        printf("\nPlease repeat the input of the vector number you would like to print:");
                        printf("\n-> ");
                        scanf("%d",&vector_choice);
                    };
                    j=0; //check if the vector is already deleted
                    for(i=0; i<=cnt_deleted_vectors; i++)
                    {
                        if(deleted_vectors[i]==vector_choice)
                        {
                            printf("\nThis vector has been deleated!\n");
                            j++;
                        }
                    }
                    if(j==0)
                    {
                        print_vector1(vector,vector_dim,vector_choice);
                        break;
                    }
                    else
                        break;
                }
                else{
                    print_vectorall(vector,vector_dim,vector_num,deleted_vectors);
                    break;
                }
                
            case 5:
                printf("\nWhich operation would you like to perform;\n");
                printf("1.Addition\n2.Subtraction\n3.Multiplication\n");
                printf("-> ");
                scanf("%d", &opperation1_choice);
                while(opperation1_choice<1 || opperation1_choice>3)
                {
                    printf("Unable to find the requested operation!\n");
                    printf("Please enter one of the existing options.\n");
                    printf("-> ");
                    scanf("%d", &opperation1_choice);
                }
                
                switch(opperation1_choice)//choosing operation
                {
                      case 1:
                        
                            printf("\nWhich arrays would you like to add;\n");
                        
                            printf("First array-> ");
                            scanf("%d",&ar1_choice);
                          
                            while(ar1_choice>array_num || ar1_choice<1)
                            {
                                printf("\nThere is no such array!");
                                printf("\nPlease repeat the input of the table number you would like to participate in the operation. ");
                                printf("-> ");
                                scanf("%d",&ar1_choice);
                            };
                            j=0;
                            for(i=0; i<=cnt_deleted_arrays; i++)
                            {
                                if(deleted_arrays[i]==ar1_choice)
                                {
                                    printf("\nThe array you entered has been deleted.!\n");
                                    j++;
                                }
                            }
                        
                            if(j!=0)
                                break;
                        
                            printf("Second array-> ");
                            scanf("%d",&ar2_choice);
                            while(ar2_choice>array_num || ar2_choice<1)
                            {
                                printf("\nThere is no such array!");
                                printf("\nPlease repeat the input of the array number you would like to participate in the operation.:");
                                printf("-> ");
                                scanf("%d",&ar2_choice);
                            };
                          
                            k=0;
                            for(i=0; i<=cnt_deleted_arrays; i++)
                            {
                                if(deleted_arrays[i]==ar2_choice)
                                {
                                    printf("\nThis array has been deleted!\n");
                                    k++;
                                }
                            }
                            if(k!=0)
                                break;
                        
                            if(j==0 && k==0)
                            {
                                sum_array(array, array1, ar1_choice, ar2_choice);
                                break;
                            }
                            
                        

                      case 2:
                          
                            printf("\nWhich arrays would you like to remove?;\n");
                            printf("First array-> ");
                            scanf("%d",&ar1_choice);
                            while(ar1_choice>array_num || ar1_choice<1)
                            {
                                printf("\nThere is no such array!");
                                printf("\nPlease repeat the input of the array number you would like to participate in the operation.:");
                                printf("\n-> ");
                                scanf("%d",&ar1_choice);
                                };
                            j=0;
                            for(i=0; i<=cnt_deleted_arrays; i++)
                            {
                                if(deleted_arrays[i]==ar1_choice)
                                {
                                    printf("\nThis array has been deleted!\n");
                                    j++;
                                }
                            }
                            
                            if(j!=0)
                                break;

                            printf("Second array-> ");
                            scanf("%d",&ar2_choice);
                            while(ar2_choice>array_num || ar2_choice<1)
                            {
                                printf("\nThere is no such array!");
                                printf("\nPlease repeat the input of the array number you would like to participate in the operation:");
                                printf("-> ");
                                scanf("%d",&ar2_choice);
                            };
                        
                            k=0;
                            for(i=0; i<=cnt_deleted_arrays; i++)
                            {
                                if(deleted_arrays[i]==ar2_choice)
                                {
                                    printf("\nThis array has been deleted!\n");
                                    k++;
                                }
                            }
                          
                            if(k!=0)
                                break;
                            if(j==0 && k==0)
                            {
                                sub_array(array, array1, ar1_choice, ar2_choice);
                                break;
                            }
                            
                        

                      case 3:
                          
                            printf("\nWhich arrays would you like to multiply?;\n");
                            printf("First array-> ");
                            scanf("%d",&ar1_choice);
                            while(ar1_choice>array_num || ar1_choice<1)
                            {
                                printf("\nThere is no such array!");
                                printf("\nPlease repeat the input of the array number you would like to participate in the operation:");
                                printf("-> ");
                                scanf("%d",&ar1_choice);
                            };
                            j=0;
                            for(i=0; i<=cnt_deleted_arrays; i++)
                            {
                                if(deleted_arrays[i]==ar1_choice)
                                {
                                    printf("\nThis array has been deleted!\n\n");
                                    j++;
                                }
                            }
                            
                            if(j!=0)
                                break;

                            printf("Second array-> ");
                            scanf("%d",&ar2_choice);
                            while(ar2_choice>array_num || ar2_choice<1)
                            {
                                printf("\nThere is no such array!");
                                printf("\nPlease repeat the input of the array number you would like to participate in the operation:");
                                printf("-> ");
                                scanf("%d",&ar2_choice);
                            };
                         
                            k=0;
                            for(i=0; i<=cnt_deleted_arrays; i++)
                            {
                                if(deleted_arrays[i]==ar2_choice)
                                {
                                    printf("\nThis array has been deleted!\n");
                                    k++;
                                }
                            }
                        
                            if(k!=0)
                                break;
                        
                            if(j==0 && k==0)
                            {
                                prod_array(array, array1, ar1_choice, ar2_choice);
                                break;
                            }
                        
                        
                }

                break;
            case 6:
                printf("\nWhich operation would you like to perform?\n");
                printf("1.Addition\n2.Subtraction\n3.Dot product\n4.Cross product\n");
                printf("-> ");
                scanf("%d", &opperation2_choice);
                while(opperation2_choice<1 || opperation2_choice>4)
                {
                    printf("Unable to find the requested operation.!\n");
                    printf("Please enter one of the existing options.\n");
                    printf("-> ");
                    scanf("%d", &opperation2_choice);
                }
                switch(opperation2_choice)//Επιλογη πραξης
                {
                      case 1:
                          
                            printf("\nWhich vectors would you like to add?\n");
                            printf("First vector-> ");
                            scanf("%d",&v1_choice);
                            while(v1_choice>vector_num || v1_choice<1)
                            {
                                printf("\nThere is no such vector!");
                                printf("\nPlease repeat the input of the vector number you would like to participate in the operation.:");
                                printf("-> ");
                                scanf("%d",&v1_choice);
                            };
                        
                            j=0;
                            for(i=0; i<=cnt_deleted_vectors; i++)
                            {
                                if(deleted_vectors[i]==v1_choice)
                                {
                                    printf("\nThis vector has been deleted!\n");
                                    j++;
                                }
                            }
                            if(j!=0)
                                break;
                        
                            printf("Second vector-> ");
                            scanf("%d",&v2_choice);
                            while(v2_choice>vector_num || v2_choice<1)
                            {
                                printf("\nThere is no such vector!");
                                printf("\nPlease repeat the input of the vector number you would like to participate in the operation:");
                                printf("-> ");
                                scanf("%d",&v2_choice);
                            };
                            k=0;
                            for(i=0; i<=cnt_deleted_vectors; i++)
                            {
                                if(deleted_vectors[i]==v1_choice)
                                {
                                    printf("\nThis vector has been deleted!\n");
                                    k++;
                                    }
                            }
                            if(k!=0)
                                break;
                          
                        
                            if(j==0 && k==0)
                            {
                                sum_vector(vector, vector_dim, v1_choice, v2_choice);
                                break;
                            }
                            
                        

                      case 2:
                         
                            printf("Which vectors would you like to substract;\n");
                            printf("First vector-> ");
                            scanf("%d",&v1_choice);
                            while(v1_choice>vector_num || v1_choice<1)
                            {
                                printf("\nThere is no such vector!");
                                printf("\nPlease repeat the input of the vector number you would like to participate in the operation:\n");
                                printf("-> ");
                                scanf("%d",&v1_choice);
                            };
                            j=0;
                            for(i=0; i<=cnt_deleted_vectors; i++)
                            {
                                if(deleted_vectors[i]==v1_choice)
                                {
                                    printf("\nThis vector has been deleted!\n");
                                    j++;
                                }
                            }
                            if(j!=0)
                                break;
                        
                            printf("Second vector-> ");
                            scanf("%d",&v2_choice);
                            while(v2_choice>vector_num || v2_choice<1)
                            {
                                printf("\nThere is no such vector!");
                                printf("\nPlease repeat the input of the vector number you would like to participate in the operation:\n");
                                printf("-> ");
                                scanf("%d",&v2_choice);
                            };
                            k=0;
                            for(i=0; i<=cnt_deleted_vectors; i++)
                            {
                                if(deleted_vectors[i]==v1_choice)
                                {
                                    printf("\nThis vector has been deleted!\n");
                                    k++;
                                }
                            }
                            if(k!=0)
                                break;
                        
                            if(j==0 && k==0)
                            {
                                sub_vector(vector, vector_dim, v1_choice, v2_choice);
                                break;
                            }
                        

                      case  3:
                            printf("Which vectors would you like to include in the dot product?\n");
                            printf("First vector-> ");
                            scanf("%d",&v1_choice);
                            while(v1_choice>vector_num || v1_choice<1)
                            {
                                printf("\nThere is no such vector!");
                                printf("\nPlease repeat the input of the vector number you would like to participate in the operation:\n");
                                printf("-> ");
                                scanf("%d",&v1_choice);
                            };
                            
                            j=0;
                            for(i=0; i<=cnt_deleted_vectors; i++)
                            {
                                if(deleted_vectors[i]==v1_choice)
                                {
                                    printf("\nThis vector has been deleted!\n");
                                    j++;
                                }
                            }
                            if(j!=0)
                                break;

                            printf("Second vector-> ");
                            scanf("%d",&v2_choice);
                            while(v2_choice>vector_num || v2_choice<1)
                            {
                                printf("\nThere is no such vector!");
                                printf("\nPlease repeat the input of the vector number you would like to participate in the operation:\n");
                                printf("-> ");
                                scanf("%d",&v2_choice);
                            };
                            k=0;
                            for(i=0; i<=cnt_deleted_vectors; i++)
                            {
                                if(deleted_vectors[i]==v1_choice)
                                {
                                    printf("\nThis vector has been deleted!\n\n");
                                    k++;
                                }
                            }
                            if(k!=0)
                                break;
                            if(j==0 && k==0)
                            {
                                dprod_vector(vector, vector_dim, v1_choice, v2_choice);
                                  break;
                            }
                        
                        

                      case 4:
                            printf("\nWhich vectors would you like to include in the cross product?\n");
                            printf("First vector-> ");
                            scanf("%d",&v1_choice);
                            while(v1_choice>vector_num || v1_choice<1)
                            {
                                printf("\nThere is no such vector!");
                                printf("\nPlease repeat the input of the vector number you would like to participate in the operation:\n");
                                printf("-> ");
                                scanf("%d",&v1_choice);
                            };
                        
                            j=0;
                            for(i=0; i<=cnt_deleted_vectors; i++)
                            {
                                if(deleted_vectors[i]==v1_choice)
                                {
                                    printf("\nThis vector has been deleted!\n");
                                    j++;
                                }
                            }
                            if(j!=0)
                                break;

                            printf("Second vector-> ");
                            scanf("%d",&v2_choice);
                            while(v2_choice>vector_num || v2_choice<1)
                            {
                                printf("\nThere is no such vector!");
                                printf("\nPlease repeat the input of the vector number you would like to participate in the operation:");
                                printf("-> ");
                                scanf("%d",&v2_choice);
                            };
                           
                            k=0;
                            for(i=0; i<=cnt_deleted_vectors; i++)
                            {
                                if(deleted_vectors[i]==v1_choice)
                                {
                                    printf("\nThis vector has been deleted!\n");
                                    k++;
                                }
                            }
                            if(k!=0)
                                break;
                            if(j==0 && k==0)
                            {
                                xprod_vector(vector, vector_dim, v1_choice, v2_choice);
                                break;
                            }
                        break;
                    }
                    break;
            //array deletion
            case 7:
                i=0;
                printf("\nChoose which array you would like to delete: ");
                printf("\n-> ");
                scanf("%d",&delete_choice);
                while(delete_arrays(deleted_arrays, &cnt_deleted_arrays,delete_choice)==0 || delete_choice<1 || delete_choice>array_num)
                {
                    printf("\nThere is no such array in the program!\nPlease repeat the input of the array you would like to delete:");
                    printf("\n-> ");
                    scanf("%d",&delete_choice);
                    i++;
                    if(i==3)
                    {
                        printf("End of attempts!\n\n");
                        break;
                    }

                }
                if(i==3)
                {
                    break;
                }
                delete_arrays(deleted_arrays, &cnt_deleted_arrays,delete_choice);
                printf("\nTable deletion successful!\n");
                break;
            //vector deletion
            case 8:
                i=0;
                printf("\nSelect which vector you want to delete: ");
                printf("\n-> ");
                scanf("%d",&delete_choice);
                while(delete_vectors(deleted_vectors, &cnt_deleted_vectors,delete_choice)==0 || delete_choice<1 || delete_choice>vector_num)
                {
                    printf("There is no such vector in the program!\nPlease repeat the input of the vector you would like to delete:");
                    printf("\n-> ");
                    scanf("%d",&delete_choice);
                    i++;
                    if(i==3)
                    {
                        printf("End of attempts!\n\n");
                        break;
                    }

                }
                if(i==3)
                {
                    break;
                }
                delete_vectors(deleted_vectors, &cnt_deleted_vectors,delete_choice);
                printf("\nVector deletion successful!\n");
                break;
           case 9:
                //Memory deallocation
                for(i=0; i<array_num; i++)
                {
                    for(j=0; j<array1[i].row; j++)
                        free(array[i][j]);
                }
                for(i=0; i<vector_num; i++)
                    free(vector[i]);
                
                printf("\nTHE PROGRAM HAS TERMINATED!!\n");
                exit(0);
                        
        }
    }
}



//Catalogue

int choices(void)
{
    int i,choice;
   
    printf("\t-------------------------\n");
    printf("\t|\tCATALOGUE\t|\n");
    printf("\t-------------------------\n");
    printf("\n\t1.Array creation\t\t\t\n");
    printf("\t2.Vector creation\t\t\t\n");
    printf("\t3.Display arrays\t\t\t\t\n");
    printf("\t4.Display vectors\t\t\t\t\n");
    printf("\t5.Matrix operations\t\t\t\t\t\n");
    printf("\t6.Vector operation\t\t\t\t\n");
    printf("\t7.Array deletion\t\t\t\t\n");
    printf("\t8.Vector deletion\t\t\t\t\n");
    printf("\t9.Exit the program\t\t\t\n");
    printf("\n\nWhich action would you like to perform? ( 1..9 )?\n");
    printf("-> ");
    scanf("%d",&choice);
    
    i=0;
    
    //checking users input
    if(choice<1 || choice>9)
    {
        do{
            printf("\nPlease enter an action from those provided in the options menu!\n");
            printf("-> ");
            scanf("%d",&choice);
            i++;
            if(i==3) //checking the number of attempts
            {
                printf("\nEnd of attempts\n\n");
                break;
            }

            
        }while(choice<1 || choice>9);
        
    }
    
    return choice;
}



//array creation
void create_array(double ***array,int array_num,struct coordinates array1[N])
{
    int row; //arrays rows 
    int coll; //arrays colls
    char filename[30]; //storing the name of the file
    FILE *fp;
    int i,j;
    

    printf("\nEnter the dimensions of the matrix you wish to create: ");
    printf("\nRows -> ");
    scanf("%d", &row);
    printf("Collumns -> ");
    scanf("%d", &coll);

    array1[array_num].row=row;
    array1[array_num].coll=coll;

    printf("\nEnter the file with the matrix: ");
    printf("\n-> ");
    scanf("%s",filename);

    fp=fopen(filename,"r");
    while(fp==NULL)
    {
        
        if(fp==NULL)
        {
            printf("\nPlease repeat the input of the file name!");
            printf("\n-> ");
            scanf("%s",filename);
            fp=fopen(filename,"r");
            
        }
    }
    //coping the values of the file to a multidimensional array

    //Dynamic memory allocation
    array[array_num]=malloc(sizeof(double *)*row);
    if(!(array[array_num]))
    {
        printf("Memory allocation failure!");
        exit(0);
    }
    for(i=0; i<row; i++)
    {
        array[array_num][i]=malloc(sizeof(double)*coll);
        if(!(array[array_num][i]))
        {
            printf("Memory allocation failure!");
            exit(0);
        }
    }
    //coping values
    for(i=0; i<row; i++)
    {
        for(j=0; j<coll; j++)
        {
            fscanf(fp,"%lf",&array[array_num][i][j]);
        }
    }

    printf("\nArray creation successful!\n\n");
    fclose(fp); 
}




//printing array
void print_array1(double ***array,struct coordinates array1[N],int num_choice)
{
    int i,j;
    int row; 
    int coll;
    int arr; //number of array 

    row=array1[num_choice-1].row;
    coll=array1[num_choice-1].coll;
    arr=(num_choice-1);

    for(i=0; i<row; i++)
    {
        for(j=0; j<coll; j++)
            printf("%10.3lf\t",array[arr][i][j]);
        printf("\n");
    }
}




//vector creation
void create_vector(double **vector,int vector_num,int vector_dim[N])
{
    FILE *fp; 
    char filename[30]; //name of the file that contains vector
    int dim; //dimension of the vector
    int i;
   
    
    printf("\nWhat is the dimension of the vector you want to add?\n");
    printf("-> ");
    scanf("%d",&dim);
    vector_dim[vector_num]=dim;
   
    vector[vector_num]=malloc(sizeof(double)*dim);
    if(!vector[vector_num])
    {
        printf("Memory allocation failure!");
        exit(0);
    }

    printf("\nEnter the file with the vector:");
    printf("\n-> ");
    scanf("%s",filename);

    //opening the file that contains the vector
    fp=fopen(filename,"r");
    while(fp==NULL)
    {
        if(fp==NULL)
        {
            printf("\nPlease repeat the input of the file name!");
            printf("\n-> ");
            scanf("%s",filename);
            fp=fopen(filename,"r");
        }
    }

    for(i=0; i<dim; i++)
        fscanf(fp,"%lf",&vector[vector_num][i]);

    printf("\nVector creation successful!\n\n");
    fclose(fp); 
}


void print_vector1(double **vector,int vector_dim[N],int vector_choice)
{
    int dim; //dimension of the vector
    int vec; //number of the vector
    int i;

    dim=vector_dim[vector_choice-1];
    vec=vector_choice-1;
    printf("\n");
    for(i=0; i<dim; i++)
        printf("%10.3lf\n",vector[vec][i]);
    printf("\n");
}

void print_arrayall(double ***array, int array_num,struct coordinates array1[N],int deleted_arrays[N])
{
    int i,j,k;
    int l,m;
    for(i=0; i<array_num; i++)
    {
        m=0;
        for(l=0; l<array_num; l++)
        {
            if((i+1)==deleted_arrays[l]) //checking if the array is already deleted
            {
                m++;
            }
        }
        if(m!=0)
            continue;
        
        for(j=0; j<array1[i].row; j++)
        {
            for(k=0; k<array1[i].coll; k++)
                printf("%8.3lf\t",array[i][j][k]);
            printf("\n");
        }
        printf("\n\n");
    }
}

void print_vectorall(double **vector,int vector_dim[N],int vector_num,int deleted_vectors[N])
{
    int i,j;
    int l,m;
    for(i=0; i<vector_num; i++)
    {
        m=0;
        printf("\n");
        for(l=0; l<vector_num; l++)
        {
            if((i+1)==deleted_vectors[l]) //checking if the vector is already deleted
            {
                m++;
            }
        }
        if(m!=0)
            continue;
        
        for(j=0; j<vector_dim[i]; j++)
            printf("%10.3f\n",vector[i][j]);
        printf("\n\n");
    }
    
    
}





//array prod
void prod_array(double ***array,struct coordinates array1[N], int ar1_choice, int ar2_choice)
{
    int i, j, k;
    double sum=0;

    int arows = array1[ar1_choice-1].row;
    int acolumns = array1[ar1_choice-1].coll;
    int brows = array1[ar2_choice-1].row;
    int bcolumns = array1[ar2_choice-1].coll;
    int ar1 = (ar1_choice-1);
    int ar2 = (ar2_choice-1);

    double **prod;
    FILE *fp;//file for storing the results 
    char filename[80];
    int save_choice;


    prod= (double **)malloc(sizeof(double *)*arows);
    if(!prod)
    {
        printf("Memory allocation failure!");
        exit(0);
    }

    for(i=0; i<arows; i++){
        prod[i]=(double *)malloc(sizeof(double)*bcolumns);
        if(!prod[i])
        {
            printf("Memory allocation failure!");
            exit(0);
        }
    }

    if(acolumns==brows){//checking if the operation can happen
    for(i=0; i<arows; i++)
    {
        for(j=0; j<bcolumns; j++)
        {
            for(k=0; k<brows; k++)
            {
                sum = sum + array[ar1][i][k] * array[ar2][k][j];
            }
            prod[i][j]=sum;
            sum=0;
        }
    }

    printf("\nThe resulting matrix is as follows:\n\n");
    for(i=0; i<arows; i++)
    {
        for(j=0; j<bcolumns; j++)
            printf("%10.3lf ", prod[i][j]);
        printf("\n");
    }


//creating file for storing the results
    printf("\n\nWould you like to save the result to a file?\n1.Yes\t2.No\n->");
    scanf("%d", &save_choice);
    while(!(save_choice==1 || save_choice==2))
    {
        printf("Please choose one answer:\n->");
        scanf("%d", &save_choice);
    }
    if(save_choice==1){
        printf("Enter the file name: ");
        scanf("%s", filename);

        fp = fopen(filename, "r");
        if(fp)
        {
            printf("\nWarning!! The file already exists.\n\n");
            fclose(fp);
        }
        else if(!fp)
        {
            fp = fopen(filename, "w");
            if(!fp)
            printf("Unable to open the file!");
        
            for(i=0; i<arows; i++)
            {
                for(j=0; j<bcolumns; j++)
                    fprintf(fp, "%10.3lf ", prod[i][j]);
                fprintf(fp, "\n");
            }
            fclose(fp);

           
            printf("\n\nFile saved successfully!\n\n");
        }
    
    }
    else if(save_choice==2)
        printf("The result was not saved to a file!\n\n");
    }
     else{
        printf("\nWarning! The number of columns in the first "
               "matrix must match the number of rows in the second matrix.\n");
        printf("Please choose a different pair of matrices..\n\n");
    }


    for(i=0; i<arows; i++)
        free(prod[i]);
    free(prod);
}




//addition
void sum_array(double ***array,struct coordinates array1[N], int ar1_choice, int ar2_choice)
{
    int i, j;

    int arows = array1[ar1_choice-1].row;
    int acolumns = array1[ar1_choice-1].coll;
    int brows = array1[ar2_choice-1].row;
    int bcolumns = array1[ar2_choice-1].coll;
    int ar1 = (ar1_choice-1);
    int ar2 = (ar2_choice-1);

    double **sum;//array for storing the result of the addition
    FILE *fp;//file for storing the results
    char filename[80];
    int save_choice;


    sum= (double **)malloc(sizeof(double *)*arows);
    if(!sum)
    {
        printf("Memory allocation failure!");
        exit(0);
    }

    for(i=0; i<arows; i++){
        sum[i]=(double *)malloc(sizeof(double)*bcolumns);
        if(!sum[i])
        {
            printf("Memory allocation failure!");
            exit(0);
        }
    }

    if(arows==brows && acolumns==bcolumns){//checking if the operation can happen
    printf("\nThe resulting matrix is as follows:\n\n");
    for(i=0; i<arows; i++){
            for(j=0; j<acolumns; j++)
            {
                sum[i][j]=array[ar1][i][j] + array[ar2][i][j];
                printf("%10.3lf\t", sum[i][j]);
            }
            printf("\n");
        }

//creating file for storing the results
    printf("\n\nWould you like to save the result to a file?\n1.Yes\t2.No\n->");
    scanf("%d", &save_choice);
    while(!(save_choice==1 || save_choice==2))
    {
        printf("Please choose one answer:\n->");
        scanf("%d", &save_choice);
    }
    if(save_choice==1){
        printf("Enter the file name: ");
        scanf("%s", filename);

        fp = fopen(filename, "r");{
        if(fp){
            printf("\nWarning!! The file already exists.\n\n");
        fclose(fp);
        }
        else if(!fp){
        fp = fopen(filename, "w");
        if(!fp)
            printf("Unable to open the file!");
        for(i=0; i<arows; i++){
        for(j=0; j<acolumns; j++)
            fprintf(fp, "%10.3lf\t", sum[i][j]);
        fprintf(fp, "\n");
        }
        fclose(fp);

        printf("\n\nFile saved successfully!\n\n");
        }
    }
    }
    else if(save_choice==2)
    printf("\nThe result was not saved to a file!\n\n");
    }
    else
        printf("\nWarning! The matrices must have the same dimensions.\n\n");


    for(i=0; i<arows; i++)
        free(sum[i]);
    free(sum);
}




//subtraction
void sub_array(double ***array,struct coordinates array1[N], int ar1_choice, int ar2_choice)
{
    int i, j;

    int arows = array1[ar1_choice-1].row;//
    int acolumns = array1[ar1_choice-1].coll;
    int brows = array1[ar2_choice-1].row;
    int bcolumns = array1[ar2_choice-1].coll;
    int ar1 = (ar1_choice-1);
    int ar2 = (ar2_choice-1);

    double **sub;
    FILE *fp;
    char filename[80];
    int save_choice;


    sub= (double **)malloc(sizeof(double *)*arows);
    if(!sub)
    {
        printf("Memory allocation failure!");
        exit(0);
    }

    for(i=0; i<arows; i++){
        sub[i]=(double *)malloc(sizeof(double)*bcolumns);
        if(!sub[i])
        {
            printf("Memory allocation failure!");
            exit(0);
        }
    }

    if(arows==brows && acolumns==bcolumns){//checking if the operation can happen
    printf("\nThe resulting matrix is as follows:\n");
    for(i=0; i<arows; i++){
            for(j=0; j<acolumns; j++)
            {
                sub[i][j]=array[ar1][i][j] - array[ar2][i][j];
                printf("%10.3lf\t", sub[i][j]);
            }
            printf("\n");
    }


//creating file to store results
    printf("\n\nWould you like to save the result to a file?\n1.Yes\t2.No\n->");
    scanf("%d", &save_choice);
    while(!(save_choice==1 || save_choice==2))
    {
        printf("Please choose one answer:\n->");
        scanf("%d", &save_choice);
    }
    if(save_choice==1){
        printf("Enter the file name:: ");
        scanf("%s", filename);

        fp = fopen(filename, "r");{
        if(fp){
            printf("\nWarning!! The file already exists.\n\n");
        fclose(fp);
        }
        else if(!fp){
        fp = fopen(filename, "w");
        if(!fp)
            printf("Unable to open the file!");
        for(i=0; i<arows; i++){
        for(j=0; j<acolumns; j++)
            fprintf(fp, "%10.3lf\t", sub[i][j]);
        fprintf(fp, "\n");
        }
        fclose(fp);

        printf("\n\nFile saved successfully!\n\n");
        }
    }
    }
    else if(save_choice==2)
    printf("The result was not saved to a file!\n\n");
    }
    else
        printf("\nWarning! The matrices must have the same dimensions.\n\n");


    for(i=0; i<arows; i++)
        free(sub[i]);
    free(sub);
}




//Vector addition
void sum_vector(double **vector,int vector_dim[N], int v1_choice, int v2_choice )
{
    int i;
    
    int dim1= vector_dim[v1_choice-1];
    int dim2= vector_dim[v2_choice-1];
    int vec1=v1_choice-1;
    int vec2=v2_choice-1;

    double *sum;
    FILE *fp;
    char filename[80];
    int save_choice;

//addition vector
    sum=malloc(sizeof(double)*dim1);
    if(!sum)
    {
        printf("Memory allocation failure!");
        exit(0);
    }

    if(dim1==dim2){
    for(i=0; i<dim1; i++)
        sum[i]=vector[vec1][i] + vector[vec2][i];

    printf("\n\nThe result of the vector addition is:\n [");
    for(i=0; i<dim1-1; i++)
        printf("%8.3lf,\t", sum[i]);
    printf("%8.3lf]\n\n", sum[dim1-1]);


    printf("\n\nWould you like to save the result to a file?\n1.Yes\t2.No\n->");
    scanf("%d", &save_choice);
    while(!(save_choice==1 || save_choice==2))
    {
        printf("Please select an option:\n->");
        scanf("%d", &save_choice);
    }
    if(save_choice==1){
        printf("Enter the file name: ");
        scanf("%s", filename);

        fp = fopen(filename, "r");{
        if(fp){
            printf("\nWarning!! The file already exists.\n\n");
        fclose(fp);
        }
        else if(!fp){
        fp = fopen(filename, "w");
        if(!fp)
            printf("Unable to open the file!\n\n");
        for(i=0; i<dim1-1; i++)
          fprintf(fp, "%8.3lf\t", sum[i]);
        fprintf(fp,"%8.3lf\n\n", sum[dim1-1]);

        fclose(fp);

        printf("\n\nFile saved successfully!\n\n");
        }
        }
    }
    else if(save_choice==2)
    printf("The result was not saved to a file!\n\n");
    }
    else
        printf("\nWarning! The vectors must have the same dimensions.\n\n");

    free(sum);
}




//vector subtraction
void sub_vector(double **vector,int vector_dim[N], int v1_choice, int v2_choice )
{
    int i;
    int dim1= vector_dim[v1_choice-1];
    int dim2= vector_dim[v2_choice-1];
    int vec1=v1_choice-1;
    int vec2=v2_choice-1;

    double *sub;
    FILE *fp;
    char filename[80];
    int save_choice;


    sub=malloc(sizeof(double)*dim1);
    if(!sub)
    {
        printf("Unable to commit memory!");
        exit(0);
    }

    if(dim1==dim2){
    for(i=0; i<dim1; i++)
        sub[i]=vector[vec1][i] - vector[vec2][i];

    printf("\n\nThe result of the vector subtraction is:\n [");
    for(i=0; i<dim1-1; i++)
        printf("%8.3lf,\t", sub[i]);
    printf("%8.3lf]\n\n", sub[dim1-1]);
    printf("\n\nWould you like to save the result to a file?\n1.Yes\t2.No\n->");
    scanf("%d", &save_choice);
    while(!(save_choice==1 || save_choice==2))
    {
        printf("Please select an option:\n->");
        scanf("%d", &save_choice);
    }
    if(save_choice==1){
        printf("Enter the file name: ");
        scanf("%s", filename);

        fp = fopen(filename, "r");{
        if(fp){
            printf("\nWarning!! The file already exists.\n\n");
        fclose(fp);
        }
        else if(!fp){
        fp = fopen(filename, "w");
        if(!fp)
            printf("Unable to open the file!");
        for(i=0; i<dim1-1; i++)
          fprintf(fp, "%8.3lf\t", sub[i]);
        fprintf(fp,"%8.3lf\n\n", sub[dim1-1]);

        fclose(fp);

        printf("\n\nFile saved successfully!\n\n");
        }
        }
    }
    else if(save_choice==2)
    printf("The result was not saved to a file!\n\n");
    }
    else
        printf("\nWarning! The vectors must have the same dimensions.\n\n");


    free(sub);
}




//dot product of vectors
void dprod_vector(double **vector,int vector_dim[N], int v1_choice, int v2_choice )
{
    int i;
    int dim1= vector_dim[v1_choice-1];
    int dim2= vector_dim[v2_choice-1];
    int vec1=v1_choice-1;
    int vec2=v2_choice-1;
    double prod=0;

    FILE *fp;
    char filename[80];
    int save_choice;

    if(dim1==dim2){
    for(i=0; i<dim1; i++)
        prod= prod + (vector[vec1][i] * vector[vec2][i]);

    printf("\n\nThe dot product of the vectors is:%10.3lf\n\n", prod);
    printf("\n\nWould you like to save the result to a file?\n1.Yes\t2.No\n->");
    scanf("%d", &save_choice);
    while(!(save_choice==1 || save_choice==2))
    {
        printf("Please choose one answer:\n->");
        scanf("%d", &save_choice);
    }
    if(save_choice==1){
        printf("Enter the file name: ");
        scanf("%s", filename);

        fp = fopen(filename, "r");{
        if(fp){
            printf("\nWarning!! The file already exists.");
        fclose(fp);
        }
        else if(!fp){
        fp = fopen(filename, "w");
        if(!fp)
            printf("Unable to open the file!");
        fprintf(fp, "%10.3lf\t", prod);

        fclose(fp);

        printf("\n\nFile saved successfully!\n\n");
        }
    }
    }
    else if(save_choice==2)
        printf("The result was not saved to a file!\n\n");
    }
    else
        printf("\nWarning! The vectors must have the same dimensions.\n\n");
}




//cross product
void xprod_vector(double **vector,int vector_dim[N], int v1_choice, int v2_choice )
{
    int i;
    int dim1= vector_dim[v1_choice-1];
    int dim2= vector_dim[v2_choice-1];
    int vec1=v1_choice-1;
    int vec2=v2_choice-1;

    double *xprod;
    FILE *fp;
    char filename[80];
    int save_choice;


    xprod=malloc(sizeof(double)*dim1);
    if(!xprod)
    {
        printf("Memory allocation failure!");
        exit(0);
    }

    if(dim1==dim2 && dim1==3){

    xprod[0] = vector[vec1][1]*vector[vec2][2] - vector[vec1][2]*vector[vec2][1];
    xprod[1] = vector[vec1][2]*vector[vec2][0] - vector[vec1][0]*vector[vec2][2];
    xprod[2] = vector[vec1][0]*vector[vec2][1] - vector[vec1][1]*vector[vec1][0];

    printf("\n\nThe cross product of the vectors is:\n [");
    for(i=0; i<dim1-1; i++)
        printf("%8.3lf,\t", xprod[i]);
    printf("%8.3lf]\n\n", xprod[dim1-1]);
    printf("\n\nWould you like to save the result to a file?\n1.Yes\t2.No\n->");
    scanf("%d", &save_choice);
    while(!(save_choice==1 || save_choice==2))
    {
        printf("Please choose one answer:\n->");
        scanf("%d", &save_choice);
    }
    if(save_choice==1){
        printf("Enter the file name: ");
        scanf("%s", filename);

        fp = fopen(filename, "r");{
        if(fp){
            printf("\nWarning!! The file already exists.");
        fclose(fp);
        }
        else if(!fp){
        fp = fopen(filename, "w");
        if(!fp)
            printf("Unable to open the file!");
        for(i=0; i<dim1; i++)
          fprintf(fp, "%10.3lf\t", xprod[i]);
        

        fclose(fp);

        printf("\n\nFile saved successfully!\n\n");
        }
        }
    }
    else if(save_choice==2)
    printf("The result was not saved to file!\n\n");
    }
    else
        printf("\nAttention! The vectors must belong to the space R^3.\n\n");

    free(xprod);
}


int delete_arrays(int deleted_arrays[N], int *cnt_deleted_arrays,int delete_choice)
{
    int i;
    if(*cnt_deleted_arrays==0)
    {
        deleted_arrays[*cnt_deleted_arrays]=delete_choice;
        (*cnt_deleted_arrays)++;
        return 1;
    }
    else
    {
        for(i=0; i<*cnt_deleted_arrays; i++)
        {
            if(deleted_arrays[i]==delete_choice) //checking if the array is already deleted
            {
                return 0;
            }
        }
        deleted_arrays[*cnt_deleted_arrays]=delete_choice;
        (*cnt_deleted_arrays)++;
        return 1;
    }
    
}


//vector deletion
int delete_vectors(int deleted_vectors[N], int *cnt_deleted_vectors,int delete_choice)
{
    int i;
    if(*cnt_deleted_vectors==0)
    {
        deleted_vectors[*cnt_deleted_vectors]=delete_choice;
        (*cnt_deleted_vectors)++;
        return 1;
    }
    else
    {
        for(i=0; i<*cnt_deleted_vectors; i++) //checking if the array is already deleted
        {
            if(deleted_vectors[i]==delete_choice)
            {
                return 0;
            }
        }
        deleted_vectors[*cnt_deleted_vectors]=delete_choice;
        (*cnt_deleted_vectors)++;
        return 1;
    }
    
}