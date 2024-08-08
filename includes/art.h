/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   art.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:39:42 by zmourtab          #+#    #+#             */
/*   Updated: 2024/08/01 10:39:44 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
#define COLORS_H

/* Text attributes */
#define RESET       "\x1b[0m"
#define BOLD        "\x1b[1m"
#define UNDERLINE   "\x1b[4m"
#define REVERSED    "\x1b[7m"

/* Foreground colors */
#define BLACK       "\x1b[30m"
#define RED         "\x1b[31m"
#define GREEN       "\x1b[32m"
#define YELLOW      "\x1b[33m"
#define BLUE        "\x1b[34m"
#define MAGENTA     "\x1b[35m"
#define CYAN        "\x1b[36m"
#define WHITE       "\x1b[37m"

/* Background colors */
#define BG_BLACK    "\x1b[40m"
#define BG_RED      "\x1b[41m"
#define BG_GREEN    "\x1b[42m"
#define BG_YELLOW   "\x1b[43m"
#define BG_BLUE     "\x1b[44m"
#define BG_MAGENTA  "\x1b[45m"
#define BG_CYAN     "\x1b[46m"
#define BG_WHITE    "\x1b[47m"

/* High-intensity foreground colors */
#define BLACK_BRIGHT    "\x1b[90m"
#define RED_BRIGHT      "\x1b[91m"
#define GREEN_BRIGHT    "\x1b[92m"
#define YELLOW_BRIGHT   "\x1b[93m"
#define BLUE_BRIGHT     "\x1b[94m"
#define MAGENTA_BRIGHT  "\x1b[95m"
#define CYAN_BRIGHT     "\x1b[96m"
#define WHITE_BRIGHT    "\x1b[97m"

/* High-intensity background colors */
#define BG_BLACK_BRIGHT    "\x1b[100m"
#define BG_RED_BRIGHT      "\x1b[101m"
#define BG_GREEN_BRIGHT    "\x1b[102m"
#define BG_YELLOW_BRIGHT   "\x1b[103m"
#define BG_BLUE_BRIGHT     "\x1b[104m"
#define BG_MAGENTA_BRIGHT  "\x1b[105m"
#define BG_CYAN_BRIGHT     "\x1b[106m"
#define BG_WHITE_BRIGHT    "\x1b[107m"

#endif /* COLORS_H */