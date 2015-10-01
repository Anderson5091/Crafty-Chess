#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "chess.h"
#include "data.h"

/* last modified 04/16/97 */
/*
********************************************************************************
*                                                                              *
*   Interrupt() is used to read in a move when the operator types something    *
*   while a search is in progress (during pondering as one example.)  this     *
*   routine reads in a command (move) and then makes two attempts to use this  *
*   input:  (1) call Option() to see if the command can be executed;  (2) try  *
*   InputMove() to see if this input is a legal move;  if so, and we are       *
*   pondering see if it matches the move we are pondering.                     *
*                                                                              *
********************************************************************************
*/
void Interrupt(int ply)
{
  int temp, *mvp;
  int i, j, left, nextc, result, time_used;
  static char save_command[64];
  int deferred=0;

/*
 ----------------------------------------------------------
|                                                          |
|   if trying to find a move to ponder, and the operator   |
|   types a command, exit a.s.a.p.                         |
|                                                          |
 ----------------------------------------------------------
*/
  if (puzzling) 
    abort_search=1;
/*
 ----------------------------------------------------------
|                                                          |
|   first check to see if this is a command by calling     |
|   Option().  Option() will return a 0 if it didn't       |
|   recognize the command; otherwise it returns a 1 if     |
|   the command was executed, or a 2 if we need to abort   |
|   the search to execute the command.                     |
|                                                          |
 ----------------------------------------------------------
*/
  else if (!xboard && !ics) {
    do {
      nextc=getc(stdin);
      if (nextc == '\n') return;
      ungetc(nextc,stdin);
      scanf("%s",input);
      if (log_file) fprintf(log_file,"%s\n",input);
      if (!strcmp(input,".")) {
        Print(1,"ok.\n");
        end_time=GetTime(time_type);
        time_used=(end_time-start_time);
        printf("time:%s ",DisplayTime(time_used));
        printf("nodes:%d\n",nodes_searched);
        for (left=0,mvp=last[0];mvp<last[1];mvp++) 
          if (!searched_this_root_move[mvp-last[0]]) left++;
        printf("%d:%d/%d  ",1,left,last[1]-last[0]);
        for (i=2;i<=ply;i++) {
          left=0;
          for (mvp=last[i-1];mvp<last[i];mvp++) 
            if (*mvp) left++;
          printf("%d:%d/%d  ",i,left,last[i]-last[i-1]);
          if (!(i%8)) printf("\n");
        }
        printf("\n");
      }
      else if (!strcmp(input,"?")) {
        Print(1,"ok.\n");
        if (thinking) {
          time_abort=1;
          abort_search=1;
        }
      }
      else {
        result=Option(input);
        if (result == 2) {
          Print(1,"ok.\n");
          if (thinking)
            Print(0,"command not legal now.\n");
          else {
            abort_search=1;
            analyze_move_read=1;
          }
        }
        else if ((result != 1) && analyze_mode) {
          Print(1,"ok.\n");
          abort_search=1;
          analyze_move_read=1;
        }
        else if (!result) {
/*
 ----------------------------------------------------------
|                                                          |
|   now, check to see if the operator typed a move.  if    |
|   so, and it matched the predicted move, switch from     |
|   pondering to thinking to start the timer.  if the      |
|   is a move, but not the predicted move, abort the       |
|   search, and start over with the right move.            |
|                                                          |
 ----------------------------------------------------------
*/
          if (pondering) {
            temp=InputMove(input,0,ChangeSide(root_wtm),1,1);
            if (temp) {
              if (auto232) {
                char *mv=OutputMoveICS(&temp);
                Delay(100);
                if (!wtm) fprintf(auto_file,"\t");
                fprintf(auto_file, " %c%c-%c%c", mv[0], mv[1], mv[2], mv[3]);
                if ((mv[4] != ' ') && (mv[4] != 0))
                fprintf(auto_file, "/%c", mv[4]);
                fprintf(auto_file, "\n");
                fflush(auto_file);
              }
              if ((From(temp) == From(ponder_move)) &&
                  (To(temp) == To(ponder_move)) &&
                  (Piece(temp) == Piece(ponder_move)) &&
                  (Captured(temp) == Captured(ponder_move)) &&
                  (Promote(temp) == Promote(ponder_move))) {
                made_predicted_move=1;
                pondering=0;
                thinking=1;
                opponent_end_time=GetTime(elapsed);
                program_start_time=GetTime(time_type);
                Print(1,"predicted move made.\n");
              }
              else
                abort_search=1;
            }
            else if (!strcmp(input,"go") || !strcmp(input,"move")) {
              abort_search=1;
            }
            else Print(0,"illegal move.\n");
          }
          else
           Print(0,"unknown command/command not legal now.\n");
        }
      }
    } while (CheckInput());
    fflush(log_file);
  }
/*
 ----------------------------------------------------------
|                                                          |
|   first check to see if this is a command by calling     |
|   Option().  Option() will return a 0 if it didn't       |
|   recognize the command; otherwise it returns a 1 if     |
|   the command was executed, or a 2 if we need to abort   |
|   the search to execute the command.                     |
|                                                          |
 ----------------------------------------------------------
*/
  else if (xboard) {
    for (i=0;i<3;i++) {
      fgets(input,80,input_stream);
      input[strlen(input)-1]='\0';
      if (!strlen(input)) {
        i--;
        continue;
      }
      if (log_file) fprintf(log_file,"%s\n",input);

      /* This is like the "." command above, but in a
	 raw form (easier to parse). We tag the start of
	 the line with "stat01:" so XBoard can recognize it.
	 In the future, additional lines (stat02, stat03, etc.)
	 can be added (if needed) without breaking backwards
	 compatibility.
	 The output is:
	 stat01: time nodes depth root_moves_left root_moves_total
	 */
	  
      if (!strcmp(input,".")) {
        end_time=GetTime(time_type);
        time_used=(end_time-start_time);

	/* Tag the line */
        printf("stat01: %d ",time_used);

	/* Note that I added ".. + q_nodes_searched" below... */
        printf("%d ",nodes_searched+q_nodes_searched);

	/* This keeps us in sync on the XBoard side.
	   Otherwise, the depth indicator will sometimes
	   go: "6 7/20" ... "6 18/20" ... "6 1/20" because
	   the depth=7 message hasn't arrived yet. */
	printf("%d ",iteration_depth); 

	/* Output stats on root moves only */
        for (left=0,mvp=last[0];mvp<last[1];mvp++) 
          if (!searched_this_root_move[mvp-last[0]]) left++;
        printf("%d %d\n",left,last[1]-last[0]);

	/* Hm... a "return" seemed the only thing that worked here */
	return;
      }
      
      for (j=1;j<strlen(input);j++)
        if (input[j] == ' ') {
          input[j]='=';
          break;
        }
      for (;j<strlen(input);j++)
        if (input[j] == ' ') {
          input[j]='/';
          break;
        }
      result=Option(input);
      if (result == 2) {
        if (thinking)
          Print(0,"command not legal now.\n");
        else {
          deferred=1;
          strcpy(save_command,input);
          abort_search=1;
          analyze_move_read=1;
        }
      }
      else if ((result != 1) && analyze_mode) {
        abort_search=1;
        analyze_move_read=1;
      }
  /*
   ----------------------------------------------------------
  |                                                          |
  |   now, check to see if the operator typed a move.  if    |
  |   so, and it matched the predicted move, switch from     |
  |   pondering to thinking to start the timer.  if the      |
  |   is a move, but not the predicted move, abort the       |
  |   search, and start over with the right move.            |
  |                                                          |
   ----------------------------------------------------------
  */
      else if (!result) {
        if (pondering) {
          temp=InputMove(input,0,ChangeSide(root_wtm),1,1);
          if (temp) {
            if ((From(temp) == From(ponder_move)) &&
                (To(temp) == To(ponder_move)) &&
                (Piece(temp) == Piece(ponder_move)) &&
                (Captured(temp) == Captured(ponder_move)) &&
                (Promote(temp) == Promote(ponder_move))) {
              made_predicted_move=1;
              pondering=0;
              thinking=1;
              opponent_end_time=GetTime(elapsed);
              program_start_time=GetTime(time_type);
            }
            else
              abort_search=1;
          }
          else if (!strcmp(input,"go") || !strcmp(input,"move")) {
            abort_search=1;
          }
          else Print(0,"illegal move.\nquit\n");
        }
      }
      if (!strstr(input,"otim") && !strstr(input,"time")) break;
    }
    if (deferred) strcpy(input,save_command);
    fflush(log_file);
  }
  else if (ics) {
    for (i=0;i<9;i++) {
      scanf("%s",input);
      if (!strcmp(input,"?")) {
        if (thinking) {
          time_abort=1;
          abort_search=1;
        }
      }
      else if (!strcmp(input,"eot")) break;
      else {
        result=Option(input);
        if (result == 2) {
          if (thinking)
            Print(0,"command not legal now.\n");
          else {
            abort_search=1;
            analyze_move_read=1;
            break;
          }
        }
        else if ((result != 1) && analyze_mode) {
          abort_search=1;
          analyze_move_read=1;
          break;
        }
        else if (!result) {
/*
 ----------------------------------------------------------
|                                                          |
|   now, check to see if the operator typed a move.  if    |
|   so, and it matched the predicted move, switch from     |
|   pondering to thinking to start the timer.  if the      |
|   is a move, but not the predicted move, abort the       |
|   search, and start over with the right move.            |
|                                                          |
 ----------------------------------------------------------
*/
          if (pondering) {
            temp=InputMove(input,0,ChangeSide(root_wtm),1,1);
            if (temp) {
              if ((From(temp) == From(ponder_move)) &&
                  (To(temp) == To(ponder_move)) &&
                  (Piece(temp) == Piece(ponder_move)) &&
                  (Captured(temp) == Captured(ponder_move)) &&
                  (Promote(temp) == Promote(ponder_move))) {
                made_predicted_move=1;
                pondering=0;
                thinking=1;
                opponent_end_time=GetTime(elapsed);
                program_start_time=GetTime(time_type);
              }
              else
                abort_search=1;
            }
            else if (!strcmp(input,"go") || !strcmp(input,"move")) {
              abort_search=1;
            }
            else Print(0,"illegal move.\n");
          }
          else
           Print(0,"unknown command/command not legal now.\n");
        }
      }
    }
    fflush(log_file);
  }
}
/*
********************************************************************************
*                                                                              *
*   SignalInterrupt() is used to catch SIGINT and SIGTERM which are used by    *
*   Xboard.  SIGINT is used when the operator clicks the "move now" button,    *
*   while SIGTERM is used to detect when Crafty is terminating.                *
*                                                                              *
********************************************************************************
*/
void SignalInterrupt(int signal_type)
{
  switch (signal_type) {
  case SIGINT:
    if (xboard) {
      if (thinking) {
        time_abort=1;
        abort_search=1;
      }
      signal(SIGINT,SignalInterrupt);
      break;
    }
  case SIGTERM:
    if (learning&book_learning && moves_out_of_book)
      LearnBook(crafty_is_white,last_search_value,0,0,1);
    if (book_file) fclose(book_file);
    if (book_lrn_file) fclose(book_lrn_file);
    if (books_file) fclose(books_file);
    if (history_file) fclose(history_file);
    if (position_file) fclose(position_file);
    if (position_lrn_file) fclose(position_lrn_file);
    if (log_file) fclose(log_file);
    exit(1);
  }
}
