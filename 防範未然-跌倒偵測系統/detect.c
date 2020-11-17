#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int main()
{
	FILE *fp, *ofp, *fa;
	int save[4][10][4], object[20][4], counter[20], objj[3][4], faa[2][5][4];  //陣列 
	int fall[5][4]; 
	int add, z, i, j, xab, yab, nab[4]; //歸檔分類
	int ab = 0, f, a, b, c, obj = 0, x, yh, xw, y; //判斷是否為同一物件
	int d, e, g, h, k, l, m, obj_h, obj_x, obj_w, obj_y, set, minus, killerswitch, ks, ii; //管理object
	int kk, kkk;

	//Set all counters to 0
	for(set = 0; set < 20; set++)
		counter[set] = 0;
		
	//判斷other與object是否相似  存入fall
	if ((fa = fopen("other.txt", "r+")) == NULL){ 
			printf("can not open file");
		}
	else{
		for(i = 0; i <5; i++){
			for(j = 0; j < 4; j++){
				if(fscanf(fa,"%d", &faa[0][i][j]) == EOF)
					break;
			}
		}
	}
	fclose(fa);
	
	if ((fa = fopen("object.txt", "r+")) == NULL){ 
			printf("can not open file");
		}
	else{
		for(i = 0; i <5; i++){
			for(j = 0; j < 4; j++){
				if(fscanf(fa,"%d", &faa[1][i][j]) == EOF)
					break;
			}
		}
	}
	fclose(fa);
	
	for(z = 0; z <2 ; z++){
		for(i = 0; i < 5; i++){
			for(j = 0; j < 4; j++){
				printf("%d ",faa[z][i][j]);
				
			}
			printf("   ");
		}
		printf("\n");
	}
	
	for(xab = 0; xab <= 2; xab++){
		for(yab = 0; yab <= 5; yab++){
			if (faa[xab][yab][0] == 0){
				//printf("%d\n", yab);
				nab[xab] = yab;
				if (nab[xab] >= ab)
					ab = nab[xab];
				break;
			}
		}
		//printf("ab %d\n", ab);
	}

       
		for(a = 0; a < ab; a++){                            	
			for(b = 0; b < ab; b++){
				
				yh = faa[1][b][3] - faa[0][a][3];
				if (yh <= 0)
					yh = yh*-1;
				x = faa[1][b][0] - faa[0][a][0];
				if (x <= 0)
					x = x*-1;
				xw = faa[1][b][2] - faa[0][b][2];
				if (xw <= 0)
					xw = xw*-1;
				y = faa[1][b][1] - faa[0][a][1];
				if (y <= 0)
					y = y*-1;
				//printf("ppppppp%d %d %d %d\n", yh, x, xw, y);
					
				if(x <= 20 && yh <= 20 && xw <= 20 && y <= 20){    //20 = 基準值  //判斷
					for(c = 0; c < 4; c++){                         //處存save進object 
						fall[a][c] = faa[0][b][c];
						//printf("sss%d", fall[a][c]);
					}
				}
			}
		}	


	for(z = 0; z < 4; z++){
		char a[2];
		char place[20];
		
		add = z+1;
		sprintf(place, "%s%d", "/home/pi/foo.txt", add);
		//printf("%s\n", place);
		
		if ((fp = fopen(place, "r+")) == NULL){ 
			printf("can not open file");
		}
		else{
			for(i = 0; i <10; i++){
				for(j = 0; j < 4; j++){
					if(fscanf(fp,"%d", &save[z][i][j]) == EOF)
						break;
					printf("%d\n", save[z][i][j]);
				}

			}
		}
		fclose(fp); 
		printf("\n");
	}
	
	for(xab = 0; xab <= 3; xab++){
		for(yab = 0; yab <= 10; yab++){
			if (save[xab][yab][0] == 0){
				//printf("%d\n", yab);
				nab[xab] = yab;
				if (nab[xab] >= ab)
					ab = nab[xab];
				break;
			}
		}
		//printf("ab %d\n", ab);
	}
	
	
//判斷是否為同一物件 
	for(f = 0; f < 3; f++){         //控制save[f][][]   //判斷a b 多少
		for(a = 0; a < ab; a++){          //控制save[f][a][]                   	
			for(b = 0; b < ab; b++){
				
				yh = (save[f+1][b][1] + save[f+1][b][3]) - (save[f][a][1] + save[f][a][3]);
				if (yh <= 0)
					yh = yh*-1;
				x = save[f+1][b][0] - save[f][a][0];
				if (x <= 0)
					x = x*-1;
				xw = (save[f+1][b][0] + save[f+1][b][2]) - (save[f][b][0] + save[f][b][2]);
				if (xw <= 0)
					xw = xw*-1;
				y = save[f+1][b][1] - save[f][a][1];
				if (y <= 0)
					y = y*-1;
				//printf("%d %d %d %d\n", yh, x, xw, y);
					
				if(x <= 20 && yh <= 20 && xw <= 20){    //20 = 基準值  //判斷
					for(c = 0; c < 4; c++){                         //處存save進object 
						object[obj][c] = save[f+1][b][c];
					}
					obj++;	
				}
			}
		}	
	}

/*	for(kkk=0; kkk<10; kkk++){	
		for(kk=0; kk<4; kk++){
			printf("\n%d", object[kkk][kk]);
		}
	}
*/
	//管理object從這開始 
	for(d = 0; d < 20; d++){         //迴圈意義: 將重複建立的物件摺疊成一個            //控制 基準object[d][]          		 
		if (object[d][0] == 0 && object[d][1] == 0 && object[d][2] == 0 && object[d][3] == 0) //若object[d][]已經是被歸零的資料則跳過不比對 
			continue;
			
		for(e = d+1; e < 20; e++){              //控制 被比對object[e][] 
			
			obj_h = object[e][3] - object[d][3];
			if (obj_h <= 0)
				obj_h = obj_h*-1;
			obj_x = object[e][0] - object[d][0];
			if (obj_x <= 0)
				obj_x = obj_x*-1;
			obj_w = object[e][2] - object[d][2];
			if (obj_w <= 0)
				obj_w = obj_w*-1;
			obj_y = object[e][1] - object[d][1];
			if (obj_y <= 0)
				obj_y = obj_y*-1;
			
			if(obj_x <= 20 && obj_y <= 20 && obj_w <= 20 && obj_h <= 20){
				for(g = 0; g < 4; g++){
					object[d][g] = object[e][g];      //將 重複的物件座標 複寫到 第一次出現的物件座標 
					object[e][g] = 0;                 //重複的物件歸零 
					counter[d]++;
				}		           
			}
		}
	
	}
	
	//清除多餘object
	for(killerswitch = 0; killerswitch < 20; killerswitch++){
		if (counter[killerswitch] < 2){
			for(ks = 0; ks < 4; ks++){
				object[killerswitch][ks] = 0;
			}
		}
	}



	for(k = 1; k < 20; k++){                    //迴圈意義: 去除object[][]中被歸零的物件 例: object[2][]為被歸零之物件，將之後的全部往前移一格，把空格填滿 
		if(object[k][0] == 0 && object[k][3] == 0){
			for(l = k; l < 19; l++){             //將被歸零的物件後面每一個資料都前移一格 
				for(m = 1; m < 4; m++){
					object[l][m] = object[l+1][m];
				}
			}
		}
	}
	//管理object在這結束   object應當會排排站，object[1][] = 物件一 , object[10][] = 物件十，並且每個object只儲存最後出現的數值 
	
	
	
	//object存檔
	if ((ofp = fopen("object.txt", "r+")) == NULL){ 
		printf("can not open file");
	}
	else{ 
		for(i = 0; i <2; i++){
			for(j = 0; j < 4; j++){
				fscanf(ofp,"%d", &objj[i][j]);
				objj[2][j] = object[0][j];
			}
		}

	}  
	fclose(ofp);
/*	for(j = 0; j < 4; j++){
				//printf("00 %d\n", objj[0][j]);
				//printf("11 %d\n", objj[1][j]);
				printf("22 %d\n", objj[2][j]);
	}
*/
	if (objj[1][0] == 0){
		if ((ofp = fopen("object.txt", "a")) == NULL){ 
			printf("can not open file");
		}
		else{
			printf("\n");
			for(ii = 0; ii <4; ii++){
				if (objj[2][ii] != 0)
					fprintf(ofp, "%d ", objj[2][ii]);
			}
		}
	}
	else{
		if ((ofp = fopen("object.txt", "w")) == NULL){ 
			printf("can not open file");
		}
		else{
			for(i = 0; i < 2; i++){
				for(ii = 0; ii <4; ii++){
						fprintf(ofp, "%d ", objj[i+1][ii]);
				}
				printf("\n");
			}
		}
	}
	fclose(ofp);
	
/*
	for(kkk=0; kkk<10; kkk++){	
		for(kk=0; kk<4; kk++){
			printf("\n%d", object[kkk][kk]);
		}
	}
*/ 

	for(kkk=0; kkk<5; kkk++){	
		for(kk=0; kk<4; kk++){
			printf("%d ", fall[kkk][kk]);
		}
		printf("\n");
	}

	for(i = 0; i < 5; i++){
		if (fall[i][3] != 0){
			if ((fall[i][3]*1.0)/(fall[i][2]*1.0) > 1.2)
				printf("save");
			else
				printf("be careful!!!");
		}
	}

	return 0;
}


