
#Compiles and executes .c files 

if [ "$1" == "" ]; then 
    echo "Usage: cx filename"
    echo "Note: the name of the c file must not contain the .c extension"
else 
    file="$1.c" 
    object="$1.o"
    rm -f "$object" "$1"
    gcc -Wall "$file" -o "$1"
    if [ "$?" != 0 ]; then 
        RED='\033[0;31m'
        echo -e "${RED}COMPILATION ERROR"
    else 
        ./"$1"
    fi
fi

