/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 23:53:03 by arrigo            #+#    #+#             */
/*   Updated: 2021/05/27 07:11:31 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H
								//CI POSSONO ESSERE PIU DATA
								//IL NEXT DEVE STARE SEMPRE ALLA FINE PER 
								//LE FUNZ DI STAMPA E DI CANCELLAZIONE NODI
typedef struct s_list
{
	void			*data;
	struct s_list	*next;

}					t_list;
/*TOOLS*/
								//SIZE ENTIRE LIST, RET INT
int		ft_list_size_list(t_list **begin);
								//SIZE LIST FROM START TO END INTERVAL
								//END CAN BE NULL
int		ft_list_size_list_interval(t_list *start, t_list *end);
								//RET INDEX NODE
int		ft_list_index_node(t_list **begin, t_list *node);
/*PRINT*/
								//PRINTA IL PRIMO DATA IN FORMATO %d
void	ft_list_print_num(t_list **begin);
								//PRINTA IL PRIMO DATA IN FORMATO %s
void	ft_list_print_str(t_list **begin);
/*ADD*/
								//INIZIALIZZA UNA NUOVA LISTA 
								//SETTA IL PUNT AL PRIMO ELEMENTO = NULL
t_list	**ft_list_init(void);
								//AGGIUNGE UN NUOVO NODO ALLA FINE DELLA LISTA
void	ft_list_add_node_back_list(t_list **begin, void *data, int type);
								//AGGIUNGE UN NUOVO NODO ALL'INIZIO DELLA LISTA
void	ft_list_add_node_front_list(t_list **begin, void *data, int type);
								//AGGIUNGE UN NODO DOPO IL NODO PASSATO COME ARG
								//RET INDIRIZZO
t_list	*ft_list_add_node_after_node(t_list *node, void *data, int type);
								//MALLOCA UN NUOVO PUNT NEW IN CUI 
								//COPIA IL CONTENUTO DI DATA
								//A SECONDA DEL TIPO PASSATO COME ARG TYPE
								//PER INFO TYPES.H
void	*ft_list_malloc_data_element(void *data, int type);
/*MOVE*/
								//SPOSTA IL NODO SRC DOPO IL NODO DEST
void	ft_list_move_node_after_node(t_list **begin, t_list *src, t_list *dest);
/*FIND*/
								//TROVA IL NODO PRECEDENTE A QUELLO PASSATO
								//COME PARAMETRO
								//RET INDIRIZZO
t_list	*ft_list_find_prev_node_by_node(t_list **begin, t_list *node);
								//TROVA IL NODO PRECEDENTE A QUELLO IN CUI 
								//SI TROVA DATA PASSATO COME PARAMETRO
								//RET INDIRIZZO
t_list	*ft_list_find_prev_node_by_data(t_list **begin, void *data);
								//TROVA UN DATO NELLA LISTA
								//RET INDIRIZZO
t_list	*ft_list_find_node_by_data(t_list **begin, void *data);
								//POSIZIONA IL PUNTATORE NELL'ULTIMO NODO 
								//RET INDIRIZZO
t_list	*ft_list_find_last_node(t_list **begin);
								//SCORRE LA POSIZIONE DI UN NODO
								//RET INDIRIZZO PROSSIMO NODO
t_list	*ft_list_find_next_node(t_list **begin, t_list *node);
/*FIND_2*/
								//TROVA L'INIDICE DEL NODO  TRAMITE DATA
int		ft_list_find_index_node_by_data(t_list **begin, void *data);
								//TROVA L'INIDICE DEL NODO  TRAMITE INDIRIZZO
int		ft_list_find_index_node_by_node(t_list **begin, t_list *node);
								//TROVA MIN, MAX, MEDIANA DI UNA LISTA
								//ANCHE DISORDINATA(VALORI INT) 
void	ft_list_find_data_min_max_med(t_list **begin, int *min, int *max, \
																	int *med);
								//TROVA L'INDICE DEL DATA "MEDIANA" IN 
								//UNA LISTA DISORDINATA
								/*THANKS FGRADIA FOR THIS FUNCTION*/
int		ft_check_pos(t_list **begin, int num);
/*DEL*/
								//CANC E FREE TUTTA LA LISTA
void	ft_list_del_list(t_list ***begin);
								//AZZERA I DATA DEL NODO
								//CONSERVA I PUNTATORI
								//NO FREE
void	ft_list_zero_node(t_list *node);
								//AZZERA TUTTI I NODI DELLA LISTA
								//CONSERVA I PUNTATORI
								//NO FREE
void	ft_list_zero_list(t_list **begin);
								//CANC E FREE UN NODO TRAMITE &DATA
void	ft_list_del_node_by_data(t_list **begin, void *data);
								//CANC E FREE UN NODO TRAMITE INDIRIZZO
void	ft_list_del_node_by_node(t_list **begin, t_list *node);
/*SWAP*/
								//SCAMBIA IL POSTO DEI NODI DELLA LISTA
void	ft_list_swap(t_list **begin, t_list *node1, t_list *node2);
/*SORT*/
								//ORDINA LA LISTA IN ORDINE CRESCENTE
								//DATA = NUM
void	ft_list_sort_incr_num(t_list **begin);
								//ORDINA LA LISTA IN ORDINE DECRESCENTE
								//DATA = NUM
void	ft_list_sort_decr_num(t_list **begin);
								//ORDINA LA LISTA IN ORDINE CRESCENTE
								//DATA = STRING
void	ft_list_sort_incr_str(t_list **begin);
								//ORDINA LA LISTA IN ORDINE DECRESCENTE
								//DATA = STRING
void	ft_list_sort_decr_str(t_list **begin);
/*SORT_2*/
								//CONTROLLA SE LA LISTA E' IN ORDINE CRESCENTE
								//DATA = NUM
int		ft_list_sort_is_sort_incr_num(t_list **begin);
								//CONTROLLA SE LA LISTA E' IN ORDINE DECRESCENTE
								//DATA = NUM
int		ft_list_sort_is_sort_decr_num(t_list **begin);
								//CONTROLLA SE LA LISTA E'IN ORDINE CRESCENTE 
								//IN UN INTERVALLO
								//DATA = NUM
int		ft_list_sort_is_sort_incr_num_interval(t_list *start, t_list *end);
								//CONTROLLA SE LA LISTA E'IN ORDINE DECRESCENTE 
								//IN UN INTERVALLO
								//DATA = NUM
int		ft_list_sort_is_sort_decr_num_interval(t_list *start, t_list *end);
#endif