# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/29 18:31:05 by jcarrete          #+#    #+#              #
#    Updated: 2022/01/30 00:37:13 by jcarrete         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LNAME = libft.a
NAME = libft

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -rf
NORME = norminette

HDIR = ../../include
SDIR = src
ODIR = obj

#################### Files for Libft ####################

FTARR_PATH = ft_array/
FTARR = ft_arr_count \
	ft_qsort_array \
	ft_qsort_insertion \
	ft_qsort_utils

FTLST_PATH = ft_lst/
FTLST = ft_lstadd_back \
	ft_lstadd_front \
	ft_lstclear \
	ft_lstdelone \
	ft_lstiter \
	ft_lstlast \
	ft_lstmap \
	ft_lstnew \
	ft_lstsize

FTMATH_PATH = ft_math/
FTMATH = ft_abs \
	ft_digits_long \
	ft_float_pwr \
	ft_is_prime \
	ft_max \
	ft_min \
	ft_pow \
	ft_sqrt

FTMEM_PATH = ft_mem/
FTMEM = ft_memalloc \
	ft_memchr \
	ft_memcmp \
	ft_memcpy \
	ft_memmove \
	ft_memset \

FTPF_PATH = ft_printf/
FTPF = ft_print_memory \
	ft_printf \
	ft_printf_conver \
	ft_printf_prtchar \
	ft_printf_prtdecexp \
	ft_printf_prtexp \
	ft_printf_prtfloat \
	ft_printf_prthex \
	ft_printf_prtint \
	ft_printf_prtoctal \
	ft_printf_prtpoint \
	ft_printf_prtret \
	ft_printf_prtspc \
	ft_printf_prtuint \
	ft_printf_prtwchar \
	ft_printf_type \
	ft_printf_prtwstr \
	ft_printf_utils \
	ft_printf_utils_eg \
	ft_printf_utils_exp \
	ft_printf_width

FTSTR_PATH = ft_str/
FTSTR = ft_atoi \
	ft_atoi_base \
	ft_ftoa \
	ft_isascii \
	ft_isspace \
	ft_itoa \
	ft_itoa_base \
	ft_putchar_fd \
	ft_split \
	ft_strappend \
	ft_strchr \
	ft_strcpy \
	ft_strdup \
	ft_strempt \
	ft_striter \
	ft_strjoin \
	ft_strcat \
	ft_strlen \
	ft_strmapi \
	ft_strcmp \
	ft_strnstr \
	ft_strrev \
	ft_strspn \
	ft_strtok \
	ft_strtrim \
	ft_substr \
	ft_swap \
	ft_tolower \
	ft_toupper \
	ft_uitoa \
	ft_uitoa_base

FILES = ft_get_next_line

FILES += $(addprefix $(FTARR_PATH),$(FTARR))
FILES += $(addprefix $(FTLST_PATH),$(FTLST))
FILES += $(addprefix $(FTMATH_PATH),$(FTMATH))
FILES += $(addprefix $(FTMEM_PATH),$(FTMEM))
FILES += $(addprefix $(FTPF_PATH),$(FTPF))
FILES += $(addprefix $(FTSTR_PATH),$(FTSTR))

SRCS = $(addprefix $(SDIR)/, $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(ODIR)/,$(addsuffix .o, $(FILES)))

#################### Colors ####################

CUT = \033[K
R = \033[31;1m
G = \033[32;1m
Y = \033[33;1m
B = \033[34;1m
P = \033[35;1m
GR = \033[30;1m
END = \033[0m

#################### Rules ####################

all: $(LNAME)

$(LNAME): $(OBJS)
	$(AR) $(LNAME) $(OBJS)
	@echo "\n$(G)[Compiled $(B)'$(LNAME)' $(G)successfully]${END}\n"

$(ODIR)/%.o: $(SDIR)/%.c $(HDIR)/$(HEAD) | $(ODIR)
	$(eval STR=$(shell echo "${CUT}\t${Y}Compiling: ${END}$<${END}"))
	@bash -c "printf '\r$(STR)\0'"
	$(CC) $(CFLAGS) -I $(HDIR) -o $@ -c $<

$(ODIR):
	@echo "\n$(GR)[Compiling $(B)'$(LNAME)'$(GR). Please, wait a few seconds...]${END}"
	mkdir -p $(ODIR)
	mkdir -p $(ODIR)/$(FTARR_PATH)
	mkdir -p $(ODIR)/$(FTLST_PATH)
	mkdir -p $(ODIR)/$(FTMATH_PATH)
	mkdir -p $(ODIR)/$(FTMEM_PATH)
	mkdir -p $(ODIR)/$(FTPF_PATH)
	mkdir -p $(ODIR)/$(FTSTR_PATH)

clean:
ifneq ($(wildcard $(ODIR)/.*),)
	@echo "\n$(GR)[Cleaning $(B)'$(NAME)'$(GR). Please wait...]${END}"
	$(RM) $(OBJS) $(ODIR)
	@echo "$(G)[Removed $(B) $(NAME) objects $(G)successfully]$(END)\n"
else
	@echo "\n$(R)[No objects to clean in $(B)$(NAME)$(R)]$(END)\n"
endif

fclean:
ifneq ("$(wildcard $(LNAME))$(wildcard $(ODIR)/.*)","")
	@echo "\n$(GR)[Cleaning $(B)'$(NAME)'$(GR). Please wait...]${END}"
ifneq ($(wildcard $(ODIR)/.*),)
	$(RM) $(OBJS) $(ODIR)
	@echo "$(G)[Removed $(B) $(NAME) objects $(G)successfully]$(END)"
endif
ifneq ("$(wildcard $(LNAME))","")
	$(RM) $(LNAME)
	@echo "$(G)[Removed $(B) $(NAME) $(G)successfully]$(END)"
endif
	@echo ""
else
	@echo "\n$(R)[Nothing to clean in $(B)$(NAME)$(R)]$(END)\n"
endif

re: fclean all

Debug: CFLAGS += -g3 -fsanitize=address
Debug: all
	@echo "\n$(Y)[Mode debug activated for $(B)'$(NAME)']$(END)\n"

norme:
	@echo "\n$(GR)[Checking $(B)'$(NORME)'$(GR) in $(B)'$(NAME)'$(GR). Please wait...]${END}"
	$(NORME) $(SDIR)/ $(HDIR) | GREP_COLORS='mt=01;32' egrep --color=always 'OK|' | \
	GREP_COLORS='mt=01;31' egrep --color=always 'Error|'
	@echo "\n$(Y)[Checked norminette in $(B)'$(NAME)' $(Y)successfully]$(END)\n"

.PHONY: all clean fclean re bonus Norme

$(V).SILENT:
