# We force the C locale here, since we are checking normal output,
# which will be translated.

LANGUAGE=
LC_ALL=C
LC_MESSAGES=
LANG=
export LANGUAGE LC_ALL LC_MESSAGES LANG
# copied from ( Haertel, et. al., 2022 )

./../src/hello_world -n > hello_world_out.txt
echo "Hello, world!" > hello_world_out_expected.txt
diff hello_world_out.txt hello_world_out_expected.txt
diff_result=$?
rm hello_world_out.txt hello_world_expected.txt
exit $diff_result
