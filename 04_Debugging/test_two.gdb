set pagination off
b range.c:29 if i >= M + S * 27 && i <= M + S * 34
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

run > /dev/null -100 100 3
quit