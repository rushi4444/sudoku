#include<iostream>
#include<iomanip>
#define YES 1
#define NO 0

using namespace std;


class sudoku{
	public:
	int value;
	int possibility;
	int num_sum;
	bool psbl_cleared;
	int is_psbl[10];
	sudoku(): value(0), possibility(9), num_sum(45), psbl_cleared(false){
		for(int i=0;i<10;i++) 
			is_psbl[i]= YES; 
	}
	void insert_num(int n){
		if( n==0) return;
		value = n;
		possibility = 1;
		num_sum = n;
		for(int i=0;i<10;i++) 
			is_psbl[i] = NO; 
		is_psbl[n] = YES;
	}
};

bool is_fully_filled(sudoku su[9][9]){
	// Verifies whether all the boxes are filled or not.
	// This function is called by is_valid.
	for(int row = 0 ; row < 9 ; row++)
		for(int col = 0 ; col < 9 ; col++)
			if(su[row][col].value == 0)
				return false;
	return true;
}

bool is_valid(sudoku su[9][9]){
	// Verifies whether Solved sudoku is valid or not.
	// This function is called by solve_sudoku.
	if(!is_fully_filled(su))
		return false;

	int hash[9] = {0,0,0,0,0,0,0,0,0};
	bool valid_sudoku;

	for(int row = 0 ; row < 9 ; row++){
		for(int i = 0; i < 9; i++)
			hash[i] = 0; 

		for(int col = 0 ; col < 9 ; col++)
			hash[su[row][col].value-1]++;

		for(int i = 0; i < 9; i++)
			if(hash[i] != 1)
				return false;
	}
	for(int col = 0 ; col < 9 ; col++){
		for(int i = 0; i < 9; i++)
			hash[i] = 0; 

		for(int row = 0 ; row < 9 ; row++)
			hash[su[row][col].value-1]++;

		for(int i = 0; i < 9; i++)
			if(hash[i] != 1)
				return false;
	}
	return true;
}
void print_sudoku(sudoku su[9][9]){
	// Prints the current state of the sudoku.
	// This function is called by main
	for(int row = 0 ; row < 9 ; row++){
		for(int col = 0 ; col < 9 ; col++){
			cout << setw(2) << su[row][col].value<<" |"; 	
			// cout << setw(2) << su[row][col].value<<","<<  setw(2) << su[row][col].possibility<<","<< setw(2) << su[row][col].num_sum<<" |"; 	
			//for(int i = 1; i< 10; i++){
			//	if( su[row][col].is_psbl[i] == YES) 	
			//		cout << i<<",";
			//}
			//cout <<"|";
		}
		cout << "\n------------------------------------\n"; 	
	}
	cout << "\n-------------------------------------------------------------------\n"; 	
}

void clear_col(sudoku su[9][9], int r, int c){
	// Clears possibility from that colum 
	// This function is called by clear_possibilities
	int v = su[r][c].value;
	for(int row = 0 ; row < 9 ; row++){
		if(row == r || su[row][c].value != 0)
			continue;
		if(su[row][c].is_psbl[v] == YES){
			su[row][c].possibility -= 1 ;
			su[row][c].num_sum -= v;
			su[row][c].is_psbl[v] = NO;
		}
	}
}
void clear_row(sudoku su[9][9], int r, int c){
	// Clears possibility from that row 
	// This function is called by clear_possibilities
	int v = su[r][c].value;
	for(int col = 0 ; col < 9 ; col++){
		if(col == c || su[r][col].value != 0)
			continue;
		if(su[r][col].is_psbl[v] == YES){
			su[r][col].possibility -= 1 ;
			su[r][col].num_sum -= v;
			su[r][col].is_psbl[v] = NO;
		}
	}
}
void clear_box(sudoku su[9][9], int r, int c){
	// Clears possibility from that box 
	// This function is called by clear_possibilities
	int v = su[r][c].value;
	for(int row = r<3?0:r<6?3:6,rowp3 = row+3; row < rowp3; row++){
		for(int col = c<3?0:c<6?3:6,colp3 = col+3; col < colp3; col++){
			//cout<< "Looking for row, colum "<< row <<","<< col <<endl;
			if((row == r && col == c) || su[row][col].value != 0){
				//cout<< "Continuing on row, colum "<< row <<","<< col <<endl;
				continue;
			}
			if(su[row][col].is_psbl[v] == YES){
				//cout<< "Clearing at row, colum "<< row <<","<< col <<endl;
				su[row][col].possibility -= 1 ;
				su[row][col].num_sum -= v;
				su[row][col].is_psbl[v] = NO;
			}
		}
	}
}
bool clear_possibilities(sudoku su[9][9]){
	// Simply clears the possibility of number in su[row][col] from its row, colum and square.
	// This function is called by solve_sudoku.
	// This function retuns if any changes are made in sudoku
	bool altered = false;
	for(int row = 0 ; row < 9 ; row++){
		for(int col = 0 ; col < 9 ; col++){
			if(su[row][col].value != 0 && su[row][col].psbl_cleared == false){
				cout << "Clearing possibilities of " << su[row][col].value << " from row " << row << "and colum " << col << endl;
				clear_col(su,row,col);
				clear_row(su,row,col);
				clear_box(su,row,col);

				su[row][col].psbl_cleared = true;
				altered = true;
			}
		}
	}
	return altered;
}

bool is_single_instance_in_a_row(sudoku su[9][9]){
	// Check if perticular number has a single possibility in a single row then sets it
	// This function is called by solve_sudoku
	// This function retuns if any changes are made in sudoku
	bool altered = false;
	for(int row = 0 ; row < 9 ; row++){
		for(int i = 1 ; i < 10 ; i++){
			int count = 0;
			int r,c,r1,c1;
			for(int col = 0 ; col < 9 ; col++){
				if(su[row][col].value == 0 && su[row][col].is_psbl[i] == YES){
					count++; 
					if(count == 2){
						r1=r;
						c1=c;
					}
					r=row;
					c=col;
				}
			}
			if(count == 1){
				cout << "Inserting number from row logic "<<r<<","<<c<<","<<i<<endl;
				su[r][c].insert_num(i);
				clear_col(su,r,c);
				clear_row(su,r,c);
				clear_box(su,r,c);
				su[r][c].psbl_cleared = true;
				altered= true; 
			}
			if(count == 2){
				if((c1<3&&c<3)||(c1>5&&c>5)||((c1>2&&c>2)&&(c1<6&&c<6))){

					for(int row = r<3?0:r<6?3:6,rowp3 = row+3; row < rowp3; row++){
						for(int col = c<3?0:c<6?3:6,colp3 = col+3; col < colp3; col++){
							if(col == c || col == c1 || su[row][col].value != 0){
								continue;
							}
							if(su[row][col].is_psbl[i] == YES){
								su[row][col].possibility -= 1 ;
								su[row][col].num_sum -= i;
								su[row][col].is_psbl[i] = NO;
								altered = true;
							}
						}
					}
				}
			}
		}
	}
	return altered;
}

bool is_single_instance_in_a_col(sudoku su[9][9]){
	// Check if perticular number has a single possibility in a single colum then sets it
	// This function is called by solve_sudoku
	// This function retuns if any changes are made in sudoku
	bool altered = false;
	for(int col = 0 ; col < 9 ; col++){
		for(int i = 1 ; i < 10 ; i++){
			int count = 0;
			int r,c,r1,c1;
			for(int row = 0 ; row < 9 ; row++){
				if(su[row][col].value == 0 && su[row][col].is_psbl[i] == YES){
					count++; 
					if(count == 2){
						r1=r;
						c1=c;
					}
					r=row;
					c=col;
				}
			}
			if(count == 1){
				cout << "Inserting number from colum logic "<<r<<","<<c<<","<<i<<endl;
				su[r][c].insert_num(i);
				clear_col(su,r,c);
				clear_row(su,r,c);
				clear_box(su,r,c);
				su[r][c].psbl_cleared = true;
				altered = true;
			}
			if(count == 2){
				if((r1<3&&r<3)||(r1>5&&r>5)||((r1>2&&r>2)&&(r1<6&&r<6))){

					for(int row = r<3?0:r<6?3:6,rowp3 = row+3; row < rowp3; row++){
						for(int col = c<3?0:c<6?3:6,colp3 = col+3; col < colp3; col++){
							if(row == r || row == r1 || su[row][col].value != 0){
								continue;
							}
							if(su[row][col].is_psbl[i] == YES){
								su[row][col].possibility -= 1 ;
								su[row][col].num_sum -= i;
								su[row][col].is_psbl[i] = NO;
								altered = true;
							}
						}
					}
				}
			}
		}
	}
	return altered;
}
bool is_single_instance_in_a_box(sudoku su[9][9]){
	// Check if perticular number has a single possibility in a single colum then sets it
	// This function is called by solve_sudoku
	// This function retuns if any changes are made in sudoku
	bool altered = false;
	int rw,clm,i;
	int r,c,r1,c1;
	int rwp3,clmp3;
	for(rw = 0 ; rw < 9 ; rw += 3){
		rwp3 = rw+3;
		for(clm = 0 ; clm < 9 ; clm += 3){
			clmp3 = clm+3;
			for(i = 1 ; i < 10 ; i++){
				int count = 0;
				for(int row = rw ; row < rwp3 ; row++)
					for(int col = clm ; col < clmp3 ; col++)
						if(su[row][col].value == 0 && su[row][col].is_psbl[i] == YES){
							count++;
							if(count == 2){
								r1 = r;
								c1 = c;
							}
							r = row;
							c = col;
						}
				if(count == 1){
					cout << "Inserting number from box logic "<<r<<","<<c<<","<<i<<endl;
					su[r][c].insert_num(i);
					clear_col(su,r,c);
					clear_row(su,r,c);
					clear_box(su,r,c);
					su[r][c].psbl_cleared = true;
					altered = true;
				}
				if(count == 2){
					if(r1 == r){
						for(int col = 0 ; col < 9 ; col++){
							if(col == c || col == c1 || su[r][col].value != 0){
								continue;
							}
							if(su[r][col].is_psbl[i] == YES){
								su[r][col].possibility -= 1 ;
								su[r][col].num_sum -= i;
								su[r][col].is_psbl[i] = NO;
								altered = true;
							}
						}
					}
					else if(c1 == c){
						for(int row = 0 ; row < 9 ; row++){
							if(row == r || row == r1 || su[row][c].value != 0){
								continue;
							}
							if(su[row][c].is_psbl[i] == YES){
								su[row][c].possibility -= 1 ;
								su[row][c].num_sum -= i;
								su[row][c].is_psbl[i] = NO;
								altered = true;
							}
						}
					}
				}
			}
		}
	}
	return altered;
}
bool is_single_possibility_in_a_cell(sudoku su[9][9]){
	// Check if only single possibility in a 1x1 cell then sets it
	// This function is called by solve_sudoku
	// This function retuns if any changes are made in sudoku
	bool altered = false;
	for(int row = 0 ; row < 9 ; row++){
		for(int col = 0 ; col < 9 ; col++){
			if(su[row][col].value == 0 && su[row][col].possibility == 1){
				int n = su[row][col].num_sum;
				cout << "Inserting number from possibility logic "<<row<<","<<col<<","<<n<<endl;
				su[row][col].insert_num(n);
				clear_col(su,row,col);
				clear_row(su,row,col);
				clear_box(su,row,col);
				su[row][col].psbl_cleared = true;
				altered = true;
			}
		}
	}
	return altered;
}

void solve_sudoku(sudoku su[9][9]){
	// This is where flow starts for solving sudoku.
	// This function is called by main
	bool altered = true;

	while(!is_valid(su)){
		//Logic 1
		while(altered){
			altered = false;
			bool alt1 = clear_possibilities(su);
			bool alt2 = is_single_possibility_in_a_cell(su);
			bool alt3 = is_single_instance_in_a_col(su);
			bool alt4 = is_single_instance_in_a_row(su);
			bool alt5 = is_single_instance_in_a_box(su);
			altered = alt1 ||alt2 || alt3 || alt4 || alt5;
		}
		//Logic 2
	}
}

int main(void){
	sudoku su[9][9],temp;
	int n=0;

	for(int row = 0 ; row < 9 ; row++){
		for(int col = 0 ; col < 9 ; col++){
			cin >> n;
			su[row][col].insert_num(n);
		}
	}

	solve_sudoku(su);

	//if( is_valid(su))
	//	cout<<"Solved\n";
	//else
	//	cout<<"not Solved\n";
	print_sudoku(su);
	return 0;
}


