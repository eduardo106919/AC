# formates the code
.PHONY: fmt
fmt:
	@-find . -name "*.c" -o -name "*.h" | xargs clang-format -verbose -i
	@shfmt -w -i 2 -l -ci .
