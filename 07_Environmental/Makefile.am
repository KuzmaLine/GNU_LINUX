CFLAGS = -Wall -g
GENERATES = src/.dirstamp src/.deps src/*.o sha1_test.sh md5_test.sh *_res.txt tmp.txt

bin_PROGRAMS=rhasher

rhasher_SOURCES=src/rhasher.c

TESTS= sha1_test.sh md5_test.sh

sha1_test.sh:
	echo 'echo "1234" > tmp.txt' >> $@
	echo 'sha1sum tmp.txt | cut -f 1 -d " " > correct_sha1_res.txt' >> $@
	echo 'echo "SHA1 tmp.txt" | ./rhasher > rhasher_sha1_res.txt' >> $@
	echo 'cmp correct_sha1_res.txt rhasher_sha1_res.txt' >> $@
	chmod +x $@

md5_test.sh:
	echo 'echo "\"bbbbbbbbbbbbbbbbbb\"" | md5sum | cut -f 1 -d " " > correct_md5_res.txt' >> $@
	echo 'echo "MD5 \"bbbbbbbbbbbbbbbbbb\"" | ./rhasher > rhasher_md5_res.txt' >> $@
	echo 'cmp correct_md5_res.txt rhasher_md5_res.txt' >> $@
	chmod +x $@

clean:
	git clean -xdf
	rm -rf ${GENERATES}