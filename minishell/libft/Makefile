# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/29 18:31:05 by jcarrete          #+#    #+#              #
#    Updated: 2021/05/02 15:56:39 by jcarrete         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LNAME = libft.a
NAME = libft

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -rf

HDIR = ../.
SDIR = src
ODIR = obj

#################### Files for Libft ####################

FTARR_PATH = ft_array/
FTARR = ft_qsort_array \
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
	ft_float_power \
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
	@echo "\n$(GR)[Compiling $(B)'$(LNAME)'$(GR). Please, wait a few seconds...]${END}\n"
	$(AR) $(LNAME) $(OBJS)
	@echo "\n$(G)[Compiled $(B)'$(LNAME)' $(G)successfully]${END}\n"

$(ODIR)/%.o: $(SDIR)/%.c $(HDIR)/$(NAME).h | $(ODIR)
	$(CC) $(CFLAGS) -I $(HDIR) -o $@ -c $<

$(ODIR):
	mkdir -p $(ODIR)
	mkdir -p $(ODIR)/$(FTARR_PATH)
	mkdir -p $(ODIR)/$(FTLST_PATH)
	mkdir -p $(ODIR)/$(FTMATH_PATH)
	mkdir -p $(ODIR)/$(FTMEM_PATH)
	mkdir -p $(ODIR)/$(FTPF_PATH)
	mkdir -p $(ODIR)/$(FTSTR_PATH)

clean:
	$(RM) $(OBJS) $(ODIR)
	@echo "\n$(R)[Cleaned $(B)$(NAME) objects $(R)successfully]$(END)\n"

fclean: clean
	$(RM) $(LNAME)
	@echo "$(R)[Removed $(B)'$(LNAME)' $(R)successfully]$(END)\n"

re: fclean all

Debug: CFLAGS += -g3 -fsanitize=address
Debug: all
	@echo "\n$(Y)[Mode debug activated for $(B)'$(NAME)']$(END)\n"

Norme:
	norminette -R CheckForbiddenSourceHeader $(SRCS) $(HDIR)/$(NAME).h
	@echo "\n$(Y)[Checked norminette in $(B)'$(NAME)' $(Y)successfully]$(END)\n"

.PHONY: all clean fclean re bonus Norme

$(V).SILENT:
