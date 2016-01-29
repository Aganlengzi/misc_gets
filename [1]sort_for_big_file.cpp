/*
在某些应用中，因为内存资源有限制，而要排序的文件很大（比如10G的文件，只有10M的内存）
主要的思想是：
1 分割文件，使分割的文件能全部加载到内存。
2 分别排序每一个分割的文件
3 合并文件

难的是合并操作
1 跌增合并，一次合并两个文件。依次类推，直到最终只剩一个文件。时间复杂度主要在读取文件，要多次读取。
2 利用堆，一次合并多个文件  时间复杂度主要取决于堆的查找。（堆主要用于查找当前最小的行）
  或者更直接的是，每次顺序查找当前内存中的最小行。
http://www.cnblogs.com/uvsjoh/archive/2012/03/24/2415343.html
*/

//单行最大长度lEN_LINE - 1
#define LEN_LINE 80

/*比较函数 因为后面要用qsort进行排序*/
int cmp(const void * str1, const void *str2)
{
    const char *p1 = (char *)str1, *p2 = (char *)str2;
    return strcmp(p1, p2);
}

/*
    文本文件以行为单位排序
*/
bool FileSort(const char *file, size_t memLimit)
{
	//文件基本大小信息
    FILE *fp;
    fp = fopen(file, "r");
    fseek(fp, 0, SEEK_END);			//将指针指向文件末尾
    size_t file_size = ftell(fp);	//文件位置指针当前位置相对于文件首的偏移字节数
    fseek(fp, 0, SEEK_SET);			//计算文件大小

	//文件分割信息
    size_t split_cnt = (file_size+memLimit-1)/memLimit;		//通用的方法，防止不足内存大小的内容被忽略
    char prefix[256] = "tttt";
    char file_t[256];
    
    int fileNo; 							//临时文件编号
    char *buff = new char[memLimit];
    if (buff == NULL)
        return false;

    size_t totalReadLen=0;                	//已读文件大小  
    size_t lineCnt = memLimit/LEN_LINE;    	//分配的空间能存下的行数
    fileNo = 1;

    //分割文件并分别排序，因为此时内存中可以放得下
    while (totalReadLen < file_size)
    {
        //生成一个临时文件名
        sprintf(file_t, "%s%d.txt", prefix, fileNo);
        FILE *fp_t = fopen(file_t, "w");
        size_t read_len=0;
        int i=0;
        //按行读取
        while ( (i<lineCnt) && fgets(buff+read_len, LEN_LINE, fp))
        {
            i++;            
            totalReadLen += strlen(buff+read_len)+1;  //算上回车
            read_len += LEN_LINE;
        }
        //排序
        qsort(buff, i, LEN_LINE, cmp);
        int j=0;
        read_len = 0;
        //写入文件
        while (j < i)
        {
            fputs(buff+read_len, fp_t);
            j++;
            read_len += LEN_LINE;
        }
        fclose(fp_t);
        fileNo++;
    }
    fclose(fp);
	
	//以上完成分割文件的排序，后面进行合并
    
	fp = fopen(file, "w");
    FILE **fp_t = (FILE **)malloc(sizeof(FILE *)*fileNo);
    bool *flg = new bool[fileNo]; 			//标识是否该从相应文件中读取新的一行

    fileNo--;
    for (int i=1; i<=fileNo; i++)
    {
        sprintf(file_t, "%s%d.txt", prefix, i);
        fp_t[i-1] = fopen(file_t, "r");
        flg[i-1] = true;
    }
    //合并
	/*
	基本思想还是比较直观的，好比每个文件中都已经按照从小到大进行了排列
	那么，每次从文件中拿一个数据放到内存中，对这些数据进行排序然后写回文件就可以了
	注意在从文件读取的时候，哪行文件被写入，下次就从读入这行的文件中读取下一行，
	每次排序的时候保持内存中的行数是一个固定值
	*/
    while (1)
    {        
        //读取新的一行
        for (int i=0; i<fileNo; i++)
        {            
            if (flg[i] )
            {
                if (fp_t[i])
                {
                    if (!fgets(buff+i*LEN_LINE, LEN_LINE, fp_t[i]))
                    {
                        fclose(fp_t[i]);
                        sprintf(file_t, "%s%d.txt", prefix, i);
                        DeleteFile(file_t);
                        buff[i*LEN_LINE] = 0;
                        fp_t[i] = NULL;
                    }
                }                
                flg[i] = false;
            }
        }
    
        int min = 0;
        //找出当前最小的行
        for (i=1; i<fileNo; i++)
        {
            if (buff[min*LEN_LINE] == 0)
                min = i;
            else if (buff[i*LEN_LINE] && strcmp(buff+min*LEN_LINE, buff+i*LEN_LINE)>0)
                min = i;
        }
        

        if (buff[min*LEN_LINE])
        {
            fputs(buff+min*LEN_LINE, fp);
            flg[min] = true;
        }
        else
            break;        
    }
    fclose(fp);

    return true;
}