#include<stdio.h>

#define FULL 0
#define EMPTY 1

void clear_all_row(int,int);
void clear_all_colum(int,int);
void clear_box(int,int,int);

int total=0,row_temp,colum_temp;

struct box
{
	int status,possibility,number,value,check[10];
};struct box node[9][9],node1[9][9];

struct check
{
	int count[10];
};struct check row_count[9],colum_count[9],box_count;


void st_node(int row,int colum,int value)
{
	int k;
	node[row][colum].value=value;
	node[row][colum].status=FULL;total++;
	node[row][colum].possibility=0;
	node[row][colum].number=0;

	for(k=1;k<10;k++)
		node[row][colum].check[k]=FULL;

	clear_all_row(row,value);
	clear_all_colum(colum,value);
	clear_box(row,colum,value);

	node[row][colum].check[0]=FULL;
}

void clear(int row,int colum,int value)
{
	node[row][colum].number-=value;
	node[row][colum].possibility--;

	if(node[row][colum].possibility==1)
		st_node(row,colum,node[row][colum].number);
}

void clear_all_row(int row,int value)
{
	int k;
	for(k=0;k<9;k++)
		if(node[row][k].check[value]==EMPTY)  //because if node.check[value] is empty then node must be empty,if node is full the node.check[value] will be automaticaly full
		{
			clear(row,k,value);
			node[row][k].check[value]=FULL;
		}
}

void clear_all_colum(int colum,int value)
{
	int k;
	for(k=0;k<9;k++)
		if(node[k][colum].check[value]==EMPTY)
		{
			clear(k,colum,value);
			node[k][colum].check[value]=FULL;
		}
}

void clear_box_wise(int row,int colum,int value)
{
	int rowp3,colump3;
	rowp3=row+3;
	colump3=colum+3;

	for(;row<rowp3;row++)
	{
		for(;colum<colump3;colum++)
			if(node[row][colum].check[value]==EMPTY)
			{
				clear(row,colum,value);
				node[row][colum].check[value]=FULL;
			}
		colum-=3;
	}
}


void clear_box_colum(int row,int colum,int value)
{
	colum_temp=colum;
	if(colum<3)
		clear_box_wise(row,colum=0,value);
	else if(colum<6)
		clear_box_wise(row,colum=3,value);
	else if(colum<9)
		clear_box_wise(row,colum=6,value);
}

void clear_box(int row,int colum,int value)
{
	row_temp=row;
	if(row<3)
		clear_box_colum(row=0,colum,value);
	else if(row<6)
		clear_box_colum(row=3,colum,value);
	else if(row<9)
		clear_box_colum(row=6,colum,value);
}

void reset_all()
{
	int row,colum,k;
	for(row=0;row<9;row++)
		for(colum=0;colum<9;colum++)
		{
			node[row][colum].possibility=9;
			node[row][colum].status=EMPTY;
			node[row][colum].number=45;

			for(k=0;k<10;k++)
				node[row][colum].check[k]=EMPTY;
		}
}

void check4row()
{
	int row,colum,cnt,colum_temp1,colum_temp2,t1,t2;
	for(row=0;row<9;row++)
		for(cnt=1;cnt<10;cnt++)
		{
			row_count[row].count[cnt]=0;
			for(colum=0;colum<9;colum++)
				if(node[row][colum].check[cnt]==EMPTY)
				{
					row_count[row].count[cnt]++;
					if(row_count[row].count[cnt]>1)
						colum_temp2=colum_temp1;
					colum_temp1=colum;
				}
			if(row_count[row].count[cnt]==1)
				st_node(row,colum_temp1,cnt);

			if(row_count[row].count[cnt]==2)
			{
				t1=colum_temp1;
				t2=colum_temp2;
				if((t1<3&&t2<3)||(t1>5&&t2>5)||((t1>2&&t2>2)&&(t1<6&&t2<6)))
				{
					node[row][colum_temp1].check[cnt]=FULL;
					node[row][colum_temp2].check[cnt]=FULL;
					clear_box(row,colum_temp1,cnt);
					node[row][colum_temp1].check[cnt]=EMPTY;
					node[row][colum_temp2].check[cnt]=EMPTY;
				}
			}

		}
}
void check4col()
{
	int row,colum,cnt,row_temp1,row_temp2,t1,t2;
	for(colum=0;colum<9;colum++)
		for(cnt=1;cnt<10;cnt++)
		{
			colum_count[colum].count[cnt]=0;
			for(row=0;row<9;row++)
				if(node[row][colum].check[cnt]==EMPTY)
				{
					colum_count[colum].count[cnt]++;
					if(colum_count[colum].count[cnt]>1)
						row_temp2=row_temp1;
					row_temp1=row;
				}
			if(colum_count[colum].count[cnt]==1)
				st_node(row_temp1,colum,cnt);

			if(colum_count[colum].count[cnt]==2)
			{
				t1=row_temp1;
				t2=row_temp2;
				if((t1<3&&t2<3)||(t1>5&&t2>5)||((t1>2&&t2>2)&&(t1<6&&t2<6)))
				{
					node[row_temp1][colum].check[cnt]=FULL;
					node[row_temp2][colum].check[cnt]=FULL;
					clear_box(row_temp1,colum,cnt);
					node[row_temp1][colum].check[cnt]=EMPTY;
					node[row_temp2][colum].check[cnt]=EMPTY;
				}
			}
		}
}

void check4box()
{
	int rw,clm,cnt,row,colum;
	int row_temp1,colum_temp1,row_temp2,colum_temp2;
	int rwp3,clmp3;
	for(rw=0;rw<9;rw+=3)
	{
		rwp3=rw+3;
		for(clm=0;clm<9;clm+=3)
		{
			clmp3=clm+3;
			for(cnt=1;cnt<10;cnt++)
			{
				box_count.count[cnt]=0;
				for(row=rw;row<rwp3;row++)
					for(colum=clm;colum<clmp3;colum++)
						if(node[row][colum].check[cnt]==EMPTY)
						{
							box_count.count[cnt]++;
							if(box_count.count[cnt]>1)
							{
								row_temp2=row_temp1;
								colum_temp2=colum_temp1;
							}
							row_temp1=row;
							colum_temp1=colum;
						}
				if(box_count.count[cnt]==1)
					st_node(row_temp1,colum_temp1,cnt);
				if(box_count.count[cnt]==2)
				{
					if(row_temp1==row_temp2)
					{
						node[row_temp1][colum_temp1].check[cnt]=FULL;
						node[row_temp2][colum_temp2].check[cnt]=FULL;
						clear_all_row(row_temp1,cnt);
						node[row_temp1][colum_temp1].check[cnt]=EMPTY;
						node[row_temp2][colum_temp2].check[cnt]=EMPTY;
					}
					if(colum_temp1==colum_temp2)
					{
						node[row_temp1][colum_temp1].check[cnt]=FULL;
						node[row_temp2][colum_temp2].check[cnt]=FULL;
						clear_all_colum(colum_temp1,cnt);
						node[row_temp1][colum_temp1].check[cnt]=EMPTY;
						node[row_temp2][colum_temp2].check[cnt]=EMPTY;
					}
				}
			}
		}
	}
}

/*int starter(int row,int colum)
  {
  int s[9][9]={{8,0,6,0,0,0,4,0,0},{0,1,0,9,0,0,0,6,0},{0,0,3,0,0,7,0,0,0},{0,3,1,4,0,0,0,2,0},{0,0,7,0,1,0,5,0,0},{0,0,0,0,0,9,8,7,0},{3,0,0,5,0,0,6,0,0},{0,0,0,0,0,2,0,9,0},{0,0,2,0,0,0,3,0,4}};
  return (s[row][colum]);
  } */

void print()
{
	int row,colum,i,j;
	clrscr();
	gotoxy(10,10);
	printf("The answer is .....");

	for(row=0,i=15;row<9;row++,i++)
	{
		for(colum=0,j=30;colum<9;colum++,j+=2)
		{
			gotoxy(j,i);
			printf("%d",node[row][colum].value);
		}
	}
}
int set(int row,int colum,int count1,int count2)
{
	int cnt1=0,cnt2=0,rowp3,clmp3;
	rowp3=row+3;
	clmp3=colum+3;
	for(;row<rowp3;row++)
	{
		for(;colum<clmp3;colum++)
		{
			if(node[row][colum].check[count1]==EMPTY)
				cnt1++;
			if(node[row][colum].check[count2]==EMPTY)
				cnt2++;
		}
		colum-=3;
	}
	if(cnt1==2&&cnt2==2)
		return(0);
	else
		return(1);
}

int look_colum(int row,int colum,int count1,int count2)
{
	if(colum<3)
		return(set(row,0,count1,count2));
	else if(colum<6)
		return(set(row,3,count1,count2));
	else if(colum<9)
		return(set(row,6,count1,count2));
}

int look(int row,int colum,int count1,int count2)
{
	if(row<3)
		return(look_colum(0,colum,count1,count2));
	else if(row<6)
		return(look_colum(3,colum,count1,count2));
	else if(row<9)
		return(look_colum(6,colum,count1,count2));
}

void thirdlogic()
{
	int row,colum,clm,clmp3,emptycount,c1,c2,s1,s2,i,samecount,ch1,ch2,clear;
	for(row=0;row<9;row++)
		for(clm=0;clm<9;clm+=3)
		{
			clmp3=clm+3;
			emptycount=0;
			for(colum=clm;colum<clmp3;colum++)
			{
				if(node[row][colum].status==EMPTY)
				{
					emptycount++;
					if(emptycount==2)
						c2=c1;
					c1=colum;
				}
			}
			if(emptycount==2)
			{
				samecount=0;
				for(i=1;i<10;i++)
				{
					ch1=node[row][c1].check[i];
					ch2=node[row][c2].check[i];
					if(ch1==EMPTY&&ch2==EMPTY)
					{
						samecount++;
						if(samecount>1)
							s2=s1;
						s1=i;
					}
				}
				if(samecount==2)
				{
					clear=look(row,c1,s1,s2);
					if(clear==0)
					{
						node[row][c1].check[s1]=FULL;
						node[row][c2].check[s2]=FULL;
						for(i=1;i<10;i++)
						{
							node[row][c1].check[i]=FULL;
							node[row][c2].check[i]=FULL;
						}
						node[row][c1].check[s1]=EMPTY;
						node[row][c2].check[s2]=EMPTY;
					}
				}
			}
		}
}

int check_sudoku()
{
	int row,colum,rowcheck[10],count,i;
	for(row=0;row<9;row++)
	{
		for(i=1;i<10;i++)
			rowcheck[i]=0;
		for(colum=0;colum<9;colum++)
			if(node[row][colum].status==FULL)
			{
				count=node[row][colum].value;
				if(rowcheck[count]==0)
					rowcheck[count]=1;
				else
					return(1);
			}
			else
				return (1);
	}
	return(0);
}
void save_current_state()
{
	int row,colum,i;
	for(row=0;row<9;row++)
		for(colum=0;colum<9;colum++)
		{
			node1[row][colum].status=node[row][colum].status;
			node1[row][colum].possibility=node[row][colum].possibility;
			node1[row][colum].value=node[row][colum].value;
			node1[row][colum].number=node[row][colum].number;
			for(i=1;i<10;i++)
				node1[row][colum].check[i]=node[row][colum].check[i];
		}
}

void rollback()
{
	int row,colum,i;
	for(row=0;row<9;row++)
		for(colum=0;colum<9;colum++)
		{
			node[row][colum].status=node1[row][colum].status;
			node[row][colum].possibility=node1[row][colum].possibility;
			node[row][colum].value=node1[row][colum].value;
			node[row][colum].number=node1[row][colum].number;
			for(i=1;i<10;i++)
				node[row][colum].check[i]=node1[row][colum].check[i];
		}
}

int assume1()
{
	int k=0,allright;
	while(k<5)
	{
		check4row();
		check4col();
		check4box();
		thirdlogic();
		k++;
	}
	allright=check_sudoku();
	if(allright==0)
	{
		print();
		getch();
		exit(1);
	}
	else
	{
		rollback();
		return(1);
	}
}

void assume()
{
	int allright,row,colum,count;
	save_current_state();
	for(row=0;row<9;row++)
		for(colum=0;colum<9;colum++)
			for(count=1;count<10;count++)
				if(node[row][colum].check[count]==EMPTY)
				{
					st_node(row,colum,count);
					if(0==assume1())
						break;
				}
}

void main()
{
	int row,colum,value,k=0;
	reset_all();
	for(row=0;row<9;row++)
		for(colum=0;colum<9;colum++)
		{
			scanf("%d",&value);
			//value=starter(row,colum);
			if(value==0)
				continue;
			st_node(row,colum,value);
		}
	while(k<10)
	{
		check4row();
		check4col();
		check4box();
		thirdlogic();
		k++;
	}
	if(total<81)
		assume();
	print();
	getch();
}
