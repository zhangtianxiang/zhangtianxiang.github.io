/****************************************\
* Author : ztx
* Title  : Build Tag Tree
\****************************************/


///////////////settings///////////////////
const char address[100] = "http://zhangtianxiang.github.io" ;
// 网站网址
const char close[100] = "fa fa-plus-square" ;
// 标签关闭
const char open[100] = "fa fa-minus-square" ;
// 标签打开
const char item[100] = "fa fa-square-o" ;
// 叶子节点

// 图标的网址 http://fontawesome.io/icons/

const char char_flag = '`' ;
// 在tree.in中用于级别的符号
// 不要忘了在主题文件中设置链接，要加着后缀.html
//////////////////////////////////////////




#include <cstdio>

FILE *fin,*fout ;

int CH , Dep , End ;
char Str[100] ;

struct node {
	int par , alone , dep ;
	char data[100] ;
	int son[100] ;
	inline void addson(int x) { son[++son[0]] = x ; }
} a[233] ;
int tota = 0 ;

inline void build(int dep,int par) {
	int p , i ;
	while (true) {
		if (End || Dep<dep) return ;
		if (Dep>dep) { build(dep+1,tota) ; continue ; }
		p = ++tota ;
		a[p].par = par , a[p].alone = true , a[p].son[0] = 0 , a[p].dep = dep ;
		a[par].addson(p) , a[par].alone = false ;
		i = 0 ;
		while (true) {
			a[p].data[i] = Str[i+dep] ;
			if (a[p].data[i] == '\0') break ;
			i ++ ;
		}
		if (fscanf(fin,"%s",Str)==EOF) { End = true ; continue ; }
		i = Dep = 0 ;
		while (Str[i++] == char_flag) Dep ++ ;
	}
}

inline void print(int o) {
	//打印o的儿子们，判断儿子是不是叶子
	int i , p ;
	// printf("<ul id=son%d>\n",o) ;
	fprintf(fout,"<ul id=son%d>\n",o) ;
	for (i = 1 ; i <= a[o].son[0] ; i ++ ) {
		p = a[o].son[i] ;
		if (a[p].alone) {
			// printf("<li style=\"PADDING-LEFT: %dpx\">\n",20*(a[p].dep)) ;
			// printf("<i class=\"fa fa-caret-right\" aria-hidden=\"true\"></i>\n") ;
			// printf("<A href=\"http://zhangtianxiang.github.io/tags/%s\" target=_blank>%s</A>\n",a[p].data,a[p].data) ;
			// printf("</li>") ;
			fprintf(fout,"<li style=\"PADDING-LEFT: %dpx\">\n",20*(a[p].dep)) ;
			fprintf(fout,"<i class=\"%s\" aria-hidden=\"true\"></i>\n",item) ;
			fprintf(fout,"<A href=\"%s/tags/%s\" target=_blank>%s</A>\n",address,a[p].data,a[p].data) ;
			fprintf(fout,"</li>") ;
		} else {
			// printf("<li style=\"PADDING-LEFT: %dpx\">\n",20*(a[p].dep)) ;
			// printf("<i class=\"fa fa-chevron-down\" aria-hidden=\"true\" id=par%d></i>\n",p) ;
			// printf("<A onclick=javascript:Change(%d) href=\"javascript:void(null)\">%s</A>\n",p,a[p].data) ;
			fprintf(fout,"<li style=\"PADDING-LEFT: %dpx\">\n",20*(a[p].dep)) ;
			fprintf(fout,"<i class=\"%s\" aria-hidden=\"true\" id=par%d></i>\n",open,p) ;
			fprintf(fout,"<A onclick=javascript:Change(%d) href=\"javascript:void(null)\">%s</A>\n",p,a[p].data) ;
			
			print(p) ;
			
			// printf("</li>") ;
			fprintf(fout,"</li>") ;
		}
	}
	// printf("</ul>\n") ;
	fprintf(fout,"</ul>\n") ;
}

int main() {
	puts("*************************");
	puts("        Hello!");
	puts("    TagsTreeMaker");
	puts("        By ztx");
	puts("*************************");
	printf("I will make tags_tree for %s\n",address) ;
	puts("If you want to change the address, please edit the cpp file.") ;

	puts("> opening tree.in") ;
	fin = fopen("tree.in","r") ;
	if (fin == NULL) {
		puts("Error: cannot open inputfile tree.in\n") ; goto END ;
	}
	puts("> opening tree.html") ;
	fout = fopen("tree.html","w") ;
	if (fout == NULL) {
		puts("\nError: cannot open outputfile tree.html\n") ; goto END ;
	}

	puts("> printing the javascript") ;
	fprintf(fout,"<script language=javascript id=clientEventHandlersJS>\n	<!--\n	function Change(i) {\n	    par = eval(\'par\' + i);\n	    son = eval(\'son\' + i);\n	    if (son.style.display == \'none\') {\n	        son.style.display = \'\';\n	    }\n	    else {\n	        son.style.display = \'none\';\n	    }\n		if (par.className == \'%s\') {\n			par.className = \'%s\';\n		}\n		else {\n			par.className = \'%s\';\n		}\n	}\n	//-->\n</script>\n",close,open,close) ;

	puts("> processing the contents of tree.in") ;
	if (fscanf(fin,"%s",Str)==EOF) {
		puts("\nError: the file tree.in is empty!\n") ; goto END ;
	}
	Dep = End = a[0].son[0] = 0 ;
	build(0,0) ;

	puts("> making file source/tree.html") ;
	print(0) ;
	END:;
	puts("> closing all files") ;
	_fcloseall() ;
	puts("> input any char to exit") ;
	getchar() ;
	return 0 ;
}