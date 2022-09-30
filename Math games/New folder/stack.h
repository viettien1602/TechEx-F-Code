struct stack
{
    int lastNode;
    int lastExpress;
    double *node;
    char *expression;
}st;

void initStack()
{
    st.lastNode = st.lastExpress = -1;
    st.node = (double*)malloc(sizeof(double));
    st.expression =(char*)malloc(sizeof(char));
}
 
void pushNode(double node)
{
    st.node[++st.lastNode] = node;
}
 
void pushExpression(char ex)
{
    st.expression[++st.lastExpress] = ex;
}
 
double popNode()
{
    return st.node[st.lastNode--];
}
 
char popExpression()
{
    return st.expression[st.lastExpress--];
}
 
char getExpression()
{
    return st.expression[st.lastExpress];
}

double getNode()
{
    return st.node[st.lastNode];
}
 
int isEmptyExpression()
{
    return st.lastExpress == -1;
}
void freeAll()
{
    free(st.expression);
    free(st.node);
}
