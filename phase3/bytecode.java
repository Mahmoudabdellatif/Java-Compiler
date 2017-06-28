.source source.txt
.class public test
.super java/lang/Object

.method public <init>()V
aload_0
invokenonvirtual java/lang/Object/<init>()V
return
.end method

.method public static main([Ljava/lang/String;)V
.limit locals 100
.limit stack 100
iconst_0
istore 1
fconst_0
fstore 2
.line 1
iconst_0
istore 3
l_0:
.line 2
ldc 0
istore 3
l_1:
.line 3
ldc 0
istore 3
l_2:
iload 3
ldc 10
if_icmplt l_4
goto l_5
l_3:
iload 3
ldc 1
iadd
istore 3
goto l_2
.line 4
l_4:
.line 5
iload 3
istore 1
getstatic      java/lang/System/out Ljava/io/PrintStream;
iload 1
invokevirtual java/io/PrintStream/println(I)V
.line 6
goto l_3
l_5:
.line 7
return
.end method
