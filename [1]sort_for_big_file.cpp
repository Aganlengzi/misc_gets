/*
��ĳЩӦ���У���Ϊ�ڴ���Դ�����ƣ���Ҫ������ļ��ܴ󣨱���10G���ļ���ֻ��10M���ڴ棩
��Ҫ��˼���ǣ�
1 �ָ��ļ���ʹ�ָ���ļ���ȫ�����ص��ڴ档
2 �ֱ�����ÿһ���ָ���ļ�
3 �ϲ��ļ�

�ѵ��Ǻϲ�����
1 �����ϲ���һ�κϲ������ļ����������ƣ�ֱ������ֻʣһ���ļ���ʱ�临�Ӷ���Ҫ�ڶ�ȡ�ļ���Ҫ��ζ�ȡ��
2 ���öѣ�һ�κϲ�����ļ�  ʱ�临�Ӷ���Ҫȡ���ڶѵĲ��ҡ�������Ҫ���ڲ��ҵ�ǰ��С���У�
  ���߸�ֱ�ӵ��ǣ�ÿ��˳����ҵ�ǰ�ڴ��е���С�С�
http://www.cnblogs.com/uvsjoh/archive/2012/03/24/2415343.html
*/

//������󳤶�lEN_LINE - 1
#define LEN_LINE 80

/*�ȽϺ��� ��Ϊ����Ҫ��qsort��������*/
int cmp(const void * str1, const void *str2)
{
    const char *p1 = (char *)str1, *p2 = (char *)str2;
    return strcmp(p1, p2);
}

/*
    �ı��ļ�����Ϊ��λ����
*/
bool FileSort(const char *file, size_t memLimit)
{
	//�ļ�������С��Ϣ
    FILE *fp;
    fp = fopen(file, "r");
    fseek(fp, 0, SEEK_END);			//��ָ��ָ���ļ�ĩβ
    size_t file_size = ftell(fp);	//�ļ�λ��ָ�뵱ǰλ��������ļ��׵�ƫ���ֽ���
    fseek(fp, 0, SEEK_SET);			//�����ļ���С

	//�ļ��ָ���Ϣ
    size_t split_cnt = (file_size+memLimit-1)/memLimit;		//ͨ�õķ�������ֹ�����ڴ��С�����ݱ�����
    char prefix[256] = "tttt";
    char file_t[256];
    
    int fileNo; 							//��ʱ�ļ����
    char *buff = new char[memLimit];
    if (buff == NULL)
        return false;

    size_t totalReadLen=0;                	//�Ѷ��ļ���С  
    size_t lineCnt = memLimit/LEN_LINE;    	//����Ŀռ��ܴ��µ�����
    fileNo = 1;

    //�ָ��ļ����ֱ�������Ϊ��ʱ�ڴ��п��Էŵ���
    while (totalReadLen < file_size)
    {
        //����һ����ʱ�ļ���
        sprintf(file_t, "%s%d.txt", prefix, fileNo);
        FILE *fp_t = fopen(file_t, "w");
        size_t read_len=0;
        int i=0;
        //���ж�ȡ
        while ( (i<lineCnt) && fgets(buff+read_len, LEN_LINE, fp))
        {
            i++;            
            totalReadLen += strlen(buff+read_len)+1;  //���ϻس�
            read_len += LEN_LINE;
        }
        //����
        qsort(buff, i, LEN_LINE, cmp);
        int j=0;
        read_len = 0;
        //д���ļ�
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
	
	//������ɷָ��ļ������򣬺�����кϲ�
    
	fp = fopen(file, "w");
    FILE **fp_t = (FILE **)malloc(sizeof(FILE *)*fileNo);
    bool *flg = new bool[fileNo]; 			//��ʶ�Ƿ�ô���Ӧ�ļ��ж�ȡ�µ�һ��

    fileNo--;
    for (int i=1; i<=fileNo; i++)
    {
        sprintf(file_t, "%s%d.txt", prefix, i);
        fp_t[i-1] = fopen(file_t, "r");
        flg[i-1] = true;
    }
    //�ϲ�
	/*
	����˼�뻹�ǱȽ�ֱ�۵ģ��ñ�ÿ���ļ��ж��Ѿ����մ�С�������������
	��ô��ÿ�δ��ļ�����һ�����ݷŵ��ڴ��У�����Щ���ݽ�������Ȼ��д���ļ��Ϳ�����
	ע���ڴ��ļ���ȡ��ʱ�������ļ���д�룬�´ξʹӶ������е��ļ��ж�ȡ��һ�У�
	ÿ�������ʱ�򱣳��ڴ��е�������һ���̶�ֵ
	*/
    while (1)
    {        
        //��ȡ�µ�һ��
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
        //�ҳ���ǰ��С����
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