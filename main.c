#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int Data;
    struct Node* Next;
    struct Node* Prev;
};
struct Node* Add(struct Node* Head1,struct Node* Head2,struct Node* result,int sign1,int sign2,int* result_sign);
struct Node* Subtract(struct Node* Head1, struct Node* Head2, struct Node* result,int sign1,int sign2, int* result_sign);
struct Node* creatList(){
    struct Node* Head = (struct Node*)malloc(sizeof(struct Node));
    if (Head == NULL) {
        printf("Out of memory!\n");
        return;
    }
    Head->Next = NULL;
    Head->Prev = NULL;
    return Head;
}
void insert(int data , struct Node* Head , struct Node* p ){        //p = position
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->Data = data;
    temp->Next = p->Next;
    temp->Prev = p;
    p->Next = temp;
    if(temp->Next != NULL)
        temp->Next->Prev = temp;
}
void display (struct Node* Head){
    struct Node* p = Head ->Next;
    if(p == NULL)
        printf("Empty list\n");
    else {
        while(p != NULL){
            printf("%d", p->Data);
            p = p->Next;
        }
        printf("\n");
    }

}
struct Node* Find(int data, struct Node* Head){
    struct Node* p = Head;
    while(p->Next != NULL){
        if(p->Data == data)
            return p;

        p = p->Next;
    }
    return p;
}
void reverse(struct Node* Head) {
    struct Node* result = Head->Next;
    struct Node* prev = NULL;
    struct Node* next = NULL;

    while (result != NULL) {
        next = result->Next;
        result->Next = prev;
        result->Prev = next;
        prev = result;
        result = next;
    }

    Head->Next = prev;
}
void Delete(int data, struct Node* Head){
    struct Node* temp = Head->Next;
    while(temp!=NULL){
        if (temp->Data!=data)
            temp = temp->Next;
        else break;
    }
    if (temp!=NULL){
        if(temp->Next!=NULL)
            temp->Next->Prev = temp->Prev;
        if(temp->Prev!=NULL)
            temp->Prev->Next = temp->Next;
        free(temp);
    }

}
void DeleteLast(struct Node* Head){
    struct Node* temp = Head->Next;
    while(temp->Next!=NULL){
        temp = temp->Next;
    }
        temp->Prev->Next = temp->Next;
        free(temp);


}

void DeleteList(struct Node* Head){
    struct Node* p;
    struct Node* temp;
    p = Head->Next;
    Head->Next = NULL;
    while(p!=NULL){
        temp = p->Next;
        free(p);
        p = temp;
    }
}
int size(struct Node* Head){
    struct Node* p = Head->Next;
    int count = 0;
    while(p!=NULL){
        count++;
        p = p->Next;
    }
    return count;
}
int value_of_lastNode(struct Node* Head){
    struct Node* p;
    int value;
    p = Head->Next;
    while(p->Next!=NULL){
        p = p->Next;
    }
    value = p->Data;
    return value;

}
int compare(struct Node* Head1,struct Node* Head2){
    int Head2_Bigger_Than_Head1=0;
    struct Node* p1 = Head1->Next;
    struct Node* p2 = Head2->Next;


    if(size(Head1)<size(Head2)){
        Head2_Bigger_Than_Head1=1;
    }
    else if (size(Head1)<size(Head2)){
        Head2_Bigger_Than_Head1=0;

    }

    else if(size(Head1)==size(Head2)){
        while(p1->Next!=NULL){
            p1 = p1->Next;
            p2 = p2->Next;
        }

        while(p1!=Head1){
            if((p1->Data) < (p2->Data)){
                Head2_Bigger_Than_Head1 = 1;
                break;
            }
            else if((p1->Data) == (p2->Data)){
                p1 = p1->Prev;
                p2 = p2->Prev;
            }


            else
                break;

        }

    }
    return Head2_Bigger_Than_Head1;
}
struct Node* Transform(char num1[],struct Node* Head,int* sign){
    long long size = strlen(num1);
    int j=NULL;
    if(num1[0]=='-'){
        *sign = 1;
    }
    for (long long i=0 ; i<size ; i++){

        if(num1[i]=='0'||num1[i]=='1'||num1[i]=='2'||num1[i]=='3'||num1[i]=='4'||num1[i]=='5'||num1[i]=='6'||num1[i]=='7'||num1[i]=='8'||num1[i]=='9'){
        switch(num1[i]){
                case '0':j=0;break;
                case '1':j=1;break;
                case '2':j=2;break;
                case '3':j=3;break;
                case '4':j=4;break;
                case '5':j=5;break;
                case '6':j=6;break;
                case '7':j=7;break;
                case '8':j=8;break;
                case '9':j=9;break;
                default : break;

            }
                insert(j,Head,Head);

        }
    }
    return Head;

} ;
struct Node* Add(struct Node* Head1,struct Node* Head2,struct Node* result,int sign1,int sign2,int* result_sign){
    if(sign1==0&&sign2==1){
        sign2=0;
        return Subtract(Head1,Head2,result,sign1,sign2,result_sign);
    }
    else if(sign1==1&&sign2==0){
        sign1=0;
        return Subtract(Head2,Head1,result,sign1,sign2,result_sign);
    }
    else{
        if(sign1==1&&sign2==1){
            *result_sign = 1;
        }
        struct Node* p1 = Head1 ->Next;
        struct Node* p2 = Head2 ->Next;
        int sum,carry = 0;

        while(p1!=NULL||p2!=NULL){
            if(p1!=NULL&&p2!=NULL)
                sum = p1->Data+p2->Data+carry;
            else{
                if(p1!=NULL)
                    sum = p1->Data+carry;
                else
                    sum = p2->Data+carry;
            }
            carry = sum/10;
            insert((sum%10),result,result);
            if(p1!=NULL)
                p1 = p1->Next;
            if(p2!=NULL)
                p2 = p2->Next;
        }
        if(carry == 1)
            insert(1,result,result);

    return result;
    }
};
struct Node* Subtract(struct Node* Head1,struct Node* Head2 ,struct Node* result,int sign1,int sign2,int* result_sign){
    if(sign1==0&&sign2==1){
        sign2=0;
        return Add(Head1,Head2,result,sign1,sign2,&result_sign);
    }
    else if(sign1==1&&sign2==0){
        sign2=1;
        return Add(Head1,Head2,result,sign1,sign2,result_sign);
    }
    else if(sign1==1&&sign2==1){
        sign1=0;
        sign2=0;
        return Subtract(Head2,Head1,result,sign1,sign2,result_sign);
    }
    else{

        struct Node* p1;
        struct Node* p2;
        if(compare(Head1,Head2)==1){
            p1 = Head2 ->Next;
            p2 = Head1 ->Next;
            *result_sign = 1;

        }
        else{
            p1 = Head1 ->Next;
            p2 = Head2 ->Next;
        }
        int diff,borrow = 0;
        while(p1!=NULL||p2!=NULL){
            if(p1!=NULL&&p2!=NULL)
                diff = p1->Data-p2->Data-borrow;
            else{
                if(p1!=NULL)
                    diff = p1->Data-borrow;
                else
                    diff = p2->Data-borrow;
            }
            if (diff<0) {
                diff += 10;
                borrow = 1;
            }
            else borrow = 0;

            insert(diff, result, result);

            if(p1!=NULL)
                p1 = p1->Next;
            if(p2!=NULL)
                p2 = p2->Next;
        }


        return result;
    }
};
struct Node* multiply(struct Node* Head1,struct Node* Head2,struct Node* result){
    struct Node* result2 = creatList();
    struct Node* result3 = creatList();


    struct Node* p2 = Head2->Next;
    struct Node* tempResult = creatList();
    int zeros = 0;

    while(p2!=NULL){
        int carry=0;
        int product;
        int remainder;
        int digit = p2->Data;
        struct Node* p1 = Head1->Next;
        for (int i = 0; i < zeros; i++) {
            insert(0, tempResult, tempResult);
            display(tempResult);
            display(Head1);
            display(Head2);
        }

        while (p1 != NULL) {
            product = (p1->Data * digit) + carry;
            carry = product / 10;
            remainder = product % 10;

            insert(remainder, tempResult, tempResult);
            display(tempResult);
            if(p1->Next==NULL&&carry>0)
                insert(carry, tempResult, tempResult);

            p1 = p1->Next;
        }
        //DeleteList(result);
        result2 = Add(result2,tempResult,result,0,0,NULL);

        //1display(tempResult);
       // display(result3);
       // display(tempResult);

       // display(result);
        p2 = p2->Next;
        zeros++;
        // Shift the temporary result by one digit

            DeleteList(tempResult);

    }
    //result2 = Add(result2, tempResult, result,0,0,NULL);
    //DeleteList(tempResult);

    return result;

};
struct Node* multiply2(struct Node* Head1,struct Node* Head2,struct Node* result,int sign1,int sign2,int* result_sign){
    if(sign1 != sign2)
        *result_sign = 1;

    for(int i=0 ; i<(size(Head1)+size(Head2));i++ ){
        insert(0,result,result);
    }
    struct Node* ptr1 = result->Next;
    struct Node* ptr2;
    struct Node* multiplican = Head1;
    struct Node* multiplier = Head2->Next;
    while(multiplier != NULL){
        multiplican = Head1->Next;
        ptr2 = ptr1;
        while(multiplican != NULL){
            int temp =0;
            temp += multiplican->Data*multiplier->Data;
            ptr2->Data += temp;
            ptr2 = ptr2->Next;
            multiplican = multiplican->Next;

        }
        ptr1 = ptr1->Next;
        multiplier = multiplier->Next;
    }
    int carry =0;
    struct Node* pp = result ;
    pp = pp -> Next ;
    int tempCarry = 0 ;

    while (pp != NULL){

        tempCarry = ( carry + pp->Data ) / 10 ;
        pp -> Data = ( carry + pp->Data ) % 10 ;
        carry = tempCarry ;

        pp = pp -> Next ;
    }

    while(value_of_lastNode(result)==0)
        DeleteLast(result);
    reverse(result);
    return result;
};
struct Node* division(struct Node* Head1,struct Node* Head2,struct Node* result,int sign1,int sign2,int* result_sign){
    reverse(Head1);
    struct Node* ptr = Head1 ->Next;
    struct Node* ptr2 ;
    struct Node* ptr3 = Head1 ->Next;
    struct Node* ptr4 = Head1 ->Next;
    struct Node* temp = creatList();
    struct Node* temp2 = creatList();
    struct Node* sub = creatList();
    struct Node* multi = creatList();
    struct Node* dividend = creatList();
    struct Node* res = creatList();

    int count = 0;
        insert((ptr->Data),temp,temp);
        insert((ptr3->Data),temp2,temp2);
            while(compare(temp,Head2)==1){
            ptr = ptr ->Next;
            ptr3 = ptr3 ->Next;
            insert(ptr->Data,temp,temp);
            insert(ptr3->Data,temp2,temp2);
            }
            while(ptr4!=NULL){
                do{
                Subtract(temp,Head2,result,0,0,NULL);
                DeleteList(temp);
                ptr2 = result ->Next;
                while(ptr2!=NULL){
                    insert((ptr2->Data),temp,temp);
                    ptr2 = ptr2->Next;
                }
                while(value_of_lastNode(temp)==0)
                    DeleteLast(temp);
                DeleteList(result);
                count++;

                }while(compare(temp,Head2)==0);
                //printf("%d",count);
                insert(count,res,res);
                multiply2(res,Head2,multi,0,0,NULL);
                reverse(multi);
                count=0;
                DeleteList(temp);
                Subtract(temp2,multi,temp,0,0,NULL);
                reverse(temp);
                while(value_of_lastNode(temp)==0)
                    DeleteLast(temp);
                //display(temp);

                for(int i=0 ; i<size(temp2);i++){
                    ptr4 = ptr4->Next;
                }
                insert(ptr4->Data,temp,temp);
                //display(temp);
               // display(Head2);
                printf("a");
                while(compare(Head2,temp)==1){
                        printf("b");
                    insert(0,res,res);
                    ptr4 = ptr4->Next;
                    insert(ptr4->Data,temp,temp);

                }

            DeleteList(multi);
            DeleteList(result);

            }
            display(res);
           // display(Head1);
            //printf("%d",compare(Head1,Head2));

   // display(res);
};




int main() {
    struct Node* Head1 = creatList();
    struct Node* Head2 = creatList();
    struct Node* result = creatList();

    int sign1=0,sign2=0,select=0;
    int result_sign =0 ;
    char num1[1000] , num2[1000];

    FILE* inputFile = fopen("input.txt", "r");
    FILE* outputFile = fopen("output.txt", "w");




    while(select!=7){
        printf("1-read the input file\n");
        printf("2-add\n");
        printf("3-subtract\n");
        printf("4-multiply\n");
        printf("5-divide\n");
        printf("6-print the result an output file\n");
        printf("7-exit\n");
        scanf("%d",&select);
        if(select==1){
            fscanf(inputFile, "%s%s", num1, num2);
            Transform(num1,Head1,&sign1);
            Transform(num2,Head2,&sign2);
            fprintf(outputFile,"done\n\n");
        }
        else if(select==2){
            fprintf(outputFile,"Addition:   ");
            DeleteList(result);
            Add(Head1,Head2,result,sign1,sign2,&result_sign);
            if (result_sign==1)
                fprintf(outputFile,"-");
            display(result);

            result_sign = 0;
        }
        else if(select==3){
            fprintf(outputFile,"Subtraction:   ");
            DeleteList(result);
            Subtract(Head1,Head2,result,sign1,sign2,&result_sign);
            if(result_sign==1)
                fprintf(outputFile,"-");
            display(result);
            result_sign = 0;
        }
        else if(select==4){
            printf("Multiplication:   ");
            DeleteList(result);
            multiply2(Head1,Head2,result,sign1,sign2,&result_sign);
            if(result_sign==1)
                fprintf(outputFile,"-");
            display(result);

        }
        else if (select==5){
            printf(outputFile,"Divide:   ");
            DeleteList(result);
            division(Head1, Head2, result, sign1, sign2, &result_sign);
            if (result_sign == 1){
                fprintf(outputFile,"-");
            }
            display(result);
        }
        else if (select==6){
            int s=size(result);
            for(int i=0 ;i<s;i++){
                fprintf(outputFile,"%d",result->Next->Data);
                result = result->Next;
            }
            fprintf(outputFile,"\n");

        }
    }
    fclose(inputFile);
    return 0;
}
