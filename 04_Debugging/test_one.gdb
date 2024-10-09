set pagination off
b range.c:29 if i % 5 == 0
command 1
        echo @@@ 
        print /d M
        echo @@@ 
        print /d N
        echo @@@ 
        print /d S
        echo @@@ 
        print /d i
        c
end

run > /dev/null 1 12
quit