/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:51:08 by rmichel-          #+#    #+#             */
/*   Updated: 2023/11/28 17:31:06 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "../libft.h"

t_list			*ft_node(char *sp, va_list arg, unsigned char mv, va_list cpy);
unsigned int	ft_count_percent(char *str);
int				ft_printf(const char *str, ...);
int				ft_putlst(t_list *list, int mv);
void			ft_del(void *content);
char			*ft_utoa(unsigned int n);
char			*ft_xtoa_caps(unsigned int n);
char			*ft_xtoa(unsigned int n);
char			*ft_ptoa(unsigned long long n);
int				ft_preput(t_list *list, int mv);

#endif
