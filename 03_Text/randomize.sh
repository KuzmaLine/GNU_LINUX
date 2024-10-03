X=0
Y=0
Y_MAX=0
text_coords=""
IFS='' 

endl=$(echo | iconv -t UTF-8 | hexdump --format '"%x"')
space=$(echo -n ' ' | iconv -t UTF-8 | hexdump --format '"%x"')

while read -r -N 1 sym
do
symbol=$(echo -ne $sym | iconv -t UTF-8 | hexdump --format '"%x"')

if test $endl = $symbol; then
    X=0
    Y=$(($Y + 1))
else
    if test $space != $symbol; then
        text_coord="($X,$Y,$symbol,$sym) $text_coord"
    fi

    X=$(($X + 1))
fi
done

text_coord=$(echo "$text_coord" | sed 's/[[:space:]]*$//')

# По какой-то причине shuf -e не работает
shuf_text_coord=$(echo $text_coord | tr " " "\n" | shuf | sed 's/(\(.*\),\(.*\),\(.*\),\(.*\))/\1 \2 \4/g')

tput clear

IFS=' '
while read -r x y val; do
    if [ $1 ]; then 
        sleep $1
    fi

    tput cup $y $x
    printf "$val"

done <<< $shuf_text_coord

tput cup $Y 0