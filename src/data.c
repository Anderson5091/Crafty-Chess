#include <stdio.h>
#include <stdlib.h>
#include "chess.h"
#include "evaluate.h"
  
  char      version[6] =                    {"11.23"};

  PLAYING_MODE mode =                     normal_mode;

  int       crafty_rating =                      2500;
  int       opponent_rating =                    2500;
  char      pgn_event[32] = {"Private Match"};
  char      pgn_site[32] = {"Birmingham, AL"};
  char      pgn_date[32] = {"????.??.??"};
  char      pgn_round[32] = {"1"};
  char      pgn_white[32] = {"unknown"};
  char      pgn_white_elo[32] = {""};
  char      pgn_black[32] = {"unknown"};
  char      pgn_black_elo[32] = {""};
  char      pgn_result[32] = {"*"};

  int       number_auto_kibitzers =                 9;

  char      auto_kibitz_list[100][20] = {
                                      {"aragorn"},
                                      {"ferret"},
                                      {"nowx"},
                                      {"rajah"},
                                      {"ratbert"},
                                      {"roborvl"},
                                      {"tcb"},
                                      {"wchessx"},
                                      {"zarkovx"}};
  

  int       computer_opponent =                     0;
  int       number_of_computers =                  60;
  char      computer_list[100][20] = {
                                      {"aha"},
                                      {"amyii"},
                                      {"aragorn"},
                                      {"aswati"},
                                      {"ban"},
                                      {"bigblue"},
                                      {"biggenius"},
                                      {"bikerbabe"},
                                      {"brause"},
                                      {"centius"},
                                      {"carokann"},
                                      {"chameleon"},
                                      {"chesskid"},
                                      {"chesst"},
                                      {"chessica"},
                                      {"chinook"},
                                      {"compute"},
                                      {"crazyknight"},
                                      {"cstal"},
                                      {"deepviolet"},
                                      {"destroyer"},
                                      {"doctorwho"},
                                      {"dominator"},
                                      {"ego-crusher"},
                                      {"ferret"},
                                      {"fitter"},
                                      {"fritzpentium"},
                                      {"gazaboy"},
                                      {"gnusurf"},
                                      {"hiarcs"},
                                      {"kerrigan"},
                                      {"kingtwoft"},
                                      {"lightpurple"},
                                      {"lonnie"},
                                      {"lyc"},
                                      {"mchesspro"},
                                      {"mephistoiii"},
                                      {"megadiep"},
                                      {"mnemonic"},
                                      {"netsurfer"},
                                      {"nowx"},
                                      {"pecabale"},
                                      {"phibs"},
                                      {"rajah"},
                                      {"ratbert"},
                                      {"rdx"},
                                      {"rebel"},
                                      {"rebel8"},
                                      {"robocop"},
                                      {"roborvl"},
                                      {"shredder"},
                                      {"silmaril"},
                                      {"spectronic"},
                                      {"turbogm"},
                                      {"tcb"},
                                      {"ultragnu"},
                                      {"wchess"},
                                      {"wchessx"},
                                      {"zarkovx"},
                                      {"zuntsu"}};

  int       number_of_GMs =                        24;
  char      GM_list[100][20] =       {
                                      {"anat"},
                                      {"devin"},
                                      {"dgurevich"},
                                      {"dlugy"},
                                      {"flamingskull"},
                                      {"gum"},
                                      {"gmsoffer"},
                                      {"junior"},
                                      {"kaidanov"},
                                      {"kc"},
                                      {"kevlar"},
                                      {"kingloek"},
                                      {"kudrin"},
                                      {"lombardy"},
                                      {"psakhis"},
                                      {"roman"},
                                      {"sagalchik"},
                                      {"securitron"},
                                      {"smirin"},
                                      {"stefansson"},
                                      {"taxi"},
                                      {"tigre"},
                                      {"vivre"},
                                      {"yofe"}};

  int       number_of_IMs =                        10;
  char      IM_list[100][20] =       {
                                      {"adolf"},
                                      {"badviking"},
                                      {"bandora"},
                                      {"imorlov"},
                                      {"impolzin"},
                                      {"laflair"},
                                      {"lsokol"},
                                      {"thutters"},
                                      {"thumpster"},
                                      {"tim"}};

  int       ics =                                   0;
  int       xboard =                                0;
  int       whisper =                               0;
  int       channel =                               0;
  int       early_exit =                           99;
  int       avoid_pondering =                       1;
  char      channel_title[32] =                  {""};
  char      book_path[32] =                 {BOOKDIR};
  char      log_path[32] =                   {LOGDIR};
  char      tb_path[32] =                     {TBDIR};
  int       initialized =                           0;
  int       kibitz =                                0;
  int       post =                                  0;
  int       log_id =                                1;
  int       move_number =                           1;
  int       wtm =                                   1;
  int       crafty_is_white =                       0;
  int       last_opponent_move =                    0;
  int       largest_positionalscore =            1000;
  int       largest_king_safety_score =          1000;
  int       search_depth =                          0;
  int       search_move =                           0;
  int       time_type =                       elapsed;
  int       nodes_between_time_checks =         10000;
  int       nodes_per_second =                  10000;

  int       time_used =                             0;
  int       time_used_opponent =                    0;
  int       auto_kibitzing =                        0;
  signed char transposition_id =                    0;
  int       check_extensions =                      1;
  int       recapture_extensions =                  1;
  int       passed_pawn_extensions =                1;
  int       one_reply_extensions =                  1;

  int       opening =                               1;
  int       middle_game =                           0;
  int       end_game =                              0;
  signed char thinking =                            0;
  signed char pondering =                           0;
  signed char puzzling =                            0;
  signed char booking =                             0;
  int       analyze_mode =                          0;
  int       annotate_mode =                         0;
  int       test_mode =                             0;
  int       analyze_move_read =                     0;
  signed char resign =                              5;
  signed char resign_counter =                      0;
  signed char resign_count =                        5;
  signed char draw_counter =                        0;
  signed char draw_count =                         10;
  int       move_limit =                          200;
  int       time_divisor=                           2;
  float     increment_factor=                       1;
  int       tc_moves =                             60;
  int       tc_time =                          180000;
  int       tc_time_remaining =                180000;
  int       tc_time_remaining_opponent =       180000;
  int       tc_moves_remaining =                   60;
  int       tc_secondary_moves =                   30;
  int       tc_secondary_time =                 90000;
  int       tc_increment =                          0;
  int       tc_sudden_death =                       0;
  int       tc_clock_start =                        0;
  int       tc_operator_time =                      0;
  int       tc_safety_margin =                      0;
  int       time_limit =                           10;
  int       force =                                 0;
  char      initial_position[80] =               {""};
  int       over =                                  0;
  float     zero_inc_factor =                       6;
  float     inc_time_multiplier =                   6;
  int       draw_score_is_zero =                    0;
  float     usage_level =                           0;
  float     usage_time =                            0;
  float     u_time=                               300;
  float     u_otime=                              300;

  char      audible_alarm =                      0x07;
#if defined(NT_i386) || defined(NT_AXP)
  int       ansi =                                  0;
#else
  int       ansi =                                  1;
#endif
  int       book_accept_mask =                    ~03;
  int       book_reject_mask =                      3;
  int       book_random =                           2;
  int       learning =                              3;
  int       moves_out_of_book =                     0;
  int       show_book =                             0;
  int       book_selection_width =                  5;
  int       ponder =                                1;
  int       trace_level =                           0;
  int       verbosity_level =                       9;
  int       noise_level =                       10000;
 
  int       hash_table_size =                    8192;
  int       log_hash_table_size =                  13;
  int       pawn_hash_table_size =               4096;
  int       log_pawn_hash_table_size =             12;

  int       default_draw_score =                 DRAW;

  int       passed_pawn_value[8] = { 0,
                                     PAWN_PASSED*2, PAWN_PASSED*3,
                                     PAWN_PASSED*5, PAWN_PASSED*8,
                                     PAWN_PASSED*12, PAWN_PASSED*20,
                                     0};

  int       connected_passer[8] =  { 0,
                                     PAWN_CONNECTED_PASSED_RANK2,
                                     PAWN_CONNECTED_PASSED_RANK3,
                                     PAWN_CONNECTED_PASSED_RANK4,
                                     PAWN_CONNECTED_PASSED_RANK5,
                                     PAWN_CONNECTED_PASSED_RANK6,
                                     PAWN_CONNECTED_PASSED_RANK7,
                                     0};
  
  int       supported_passer[8] =  { 0,
                                     PAWN_SUPPORTED_PASSED_RANK2,
                                     PAWN_SUPPORTED_PASSED_RANK3,
                                     PAWN_SUPPORTED_PASSED_RANK4,
                                     PAWN_SUPPORTED_PASSED_RANK5,
                                     PAWN_SUPPORTED_PASSED_RANK6,
                                     PAWN_SUPPORTED_PASSED_RANK7,
                                     0};
  int       reduced_material_passer[20] = { 100,100,90,90,80,80,70,70,60,60,
                                             50,50,40,40,30,30,20,20,10,10};

  int       outside_passed[128] = {1000,1000, 600, 600, 500, 400, 400, 400,
                                    300, 300, 300, 300, 200, 200, 200, 200,
                                    100, 100, 100, 100,  50,  50,  50,  50,
                                     50,  50,  50,  50,  50,  50,  50,  50,
                                     50,  50,  50,  50,  50,  50,  50,  50,
                                     50,  50,  50,  50,  50,  50,  50,  50,
                                     50,  50,  50,  50,  50,  50,  50,  50,
                                     50,  50,  50,  50,  50,  50,  50,  50,
                                     50,  50,  50,  50,  50,  50,  50,  50,
                                     50,  50,  50,  50,  50,  50,  50,  50,
                                     50,  50,  50,  50,  50,  50,  50,  50,
                                     50,  50,  50,  50,  50,  50,  50,  50,
                                     50,  50,  50,  50,  50,  50,  50,  50,
                                     50,  50,  50,  50,  50,  50,  50,  50,
                                     50,  50,  50,  50,  50,  50,  50,  50,
                                     50,  50,  50,  50,  50,  50,  50,  50};
    
  char      distance[8] = {16, 16, 16, 12, 6, 4, 2, 0};

  char      square_color[64]  = { 1, 0, 1, 0, 1, 0, 1, 0,
                                  0, 1, 0, 1, 0, 1, 0, 1,
                                  1, 0, 1, 0, 1, 0, 1, 0,
                                  0, 1, 0, 1, 0, 1, 0, 1,
                                  1, 0, 1, 0, 1, 0, 1, 0,
                                  0, 1, 0, 1, 0, 1, 0, 1,
                                  1, 0, 1, 0, 1, 0, 1, 0,
                                  0, 1, 0, 1, 0, 1, 0, 1 };

  int       b_n_mate_dark_squares[64] = 
                             { 2000, 1500, 1000,  500, -500,-1000,-1500,-2000,
                               1500, 1500, 1000,  500, -500,-1000,-1500,-1500,
                               1000, 1000, 1000,  500, -500,-1000,-1000,-1000,
                                500,  500,  500,  500, -500, -500, -500, -500,
                               -500, -500, -500, -500,  500,  500,  500,  500,
                              -1000,-1000,-1000, -500,  500, 1000, 1000, 1000,
                              -1500,-1500,-1000, -500,  500, 1000, 1500, 1500,
                              -2000,-1500,-1000, -500,  500, 1000, 1500, 2000};

  int       b_n_mate_light_squares[64] =
                             {-2000,-1500,-1000, -500,  500, 1000, 1500, 2000,
                              -1500,-1500,-1000, -500,  500, 1000, 1500, 1500,
                              -1000,-1000,-1000, -500,  500, 1000, 1000, 1000,
                               -500, -500, -500, -500,  500,  500,  500,  500,
                                500,  500,  500,  500, -500, -500, -500, -500,
                               1000, 1000, 1000,  500, -500,-1000,-1000,-1000,
                               1500, 1500, 1000,  500, -500,-1000,-1500,-1500,
                               2000, 1500, 1000,  500, -500,-1000,-1500,-2000};

  int       mate[64] =           {2800,2600,2400,2200,2200,2400,2600,2800,
                                  2600,1600,1400,1200,1200,1400,1600,2600,
                                  2400,1400, 400, 200, 200, 400,1400,2400,
                                  2200,1200, 200,   0,   0, 200,1200,2200,
                                  2200,1200, 200,   0,   0, 200,1200,2200,
                                  2400,1400, 400, 200, 200, 400,1400,2400,
                                  2600,1600,1400,1200,1200,1400,1600,2600,
                                  2800,2600,2400,2200,2200,2400,2600,2800};


#if !defined(COMPACT_ATTACKS)
  int            bishop_shift_rl45[64] = { 63, 61, 58, 54, 49, 43, 36, 28,
                                           61, 58, 54, 49, 43, 36, 28, 21,
                                           58, 54, 49, 43, 36, 28, 21, 15,
                                           54, 49, 43, 36, 28, 21, 15, 10,
                                           49, 43, 36, 28, 21, 15, 10,  6,
                                           43, 36, 28, 21, 15, 10,  6,  3,
                                           36, 28, 21, 15, 10,  6,  3,  1,
                                           28, 21, 15, 10,  6,  3,  1,  0 };

  int            bishop_shift_rr45[64] = { 
                                           28, 36, 43, 49, 54, 58, 61, 63,
                                           21, 28, 36, 43, 49, 54, 58, 61,
                                           15, 21, 28, 36, 43, 49, 54, 58,
                                           10, 15, 21, 28, 36, 43, 49, 54,
                                            6, 10, 15, 21, 28, 36, 43, 49,
                                            3,  6, 10, 15, 21, 28, 36, 43,
                                            1,  3,  6, 10, 15, 21, 28, 36,
                                            0,  1,  3,  6, 10, 15, 21, 28 };
#endif

  char            white_outpost[64] = { 0, 0, 0, 0, 0, 0, 0, 0,
                                        0, 0, 0, 0, 0, 0, 0, 0,
                                        0, 0, 0, 0, 0, 0, 0, 0,
                                        0, 0, 0, 1, 1, 0, 0, 0,
                                        0, 0, 2, 3, 3, 2, 0, 0,
                                        0, 1, 2, 3, 3, 2, 1, 0,
                                        0, 0, 0, 1, 1, 0, 0, 0,
                                        0, 0, 0, 0, 0, 0, 0, 0 };

  char            black_outpost[64] = { 0, 0, 0, 0, 0, 0, 0, 0,
                                        0, 0, 0, 1, 1, 0, 0, 0,
                                        0, 1, 2, 3, 3, 2, 1, 0,
                                        0, 0, 2, 3, 3, 2, 0, 0,
                                        0, 0, 0, 1, 1, 0, 0, 0,
                                        0, 0, 0, 0, 0, 0, 0, 0,
                                        0, 0, 0, 0, 0, 0, 0, 0,
                                        0, 0, 0, 0, 0, 0, 0, 0 };

  char           push_extensions[64] = { 0, 0, 0, 0, 0, 0, 0, 0,
                                         1, 1, 1, 1, 1, 1, 1, 1,
                                         0, 0, 0, 0, 0, 0, 0, 0,
                                         0, 0, 0, 0, 0, 0, 0, 0,
                                         0, 0, 0, 0, 0, 0, 0, 0,
                                         0, 0, 0, 0, 0, 0, 0, 0,
                                         1, 1, 1, 1, 1, 1, 1, 1,
                                         0, 0, 0, 0, 0, 0, 0, 0 };

  int  knight_value_w[64] = {-300, -100, -100, -100, -100, -100, -100, -300,
                             -100,  -50,    0,    0,    0,    0,  -50, -100,
                             -100,    0,   50,   50,   50,   50,    0, -100,
                             -100,    0,   50,   80,   80,   50,    0, -100,
                             -100,    0,   80,   80,   80,   80,    0, -100,
                             -100,    0,   80,   80,   80,   80,    0, -100,
                             -200, -100,  -10, -100, -100, -100, -100, -200,
                             -500, -200, -200, -200, -200, -200, -200, -500};

  int  knight_value_b[64] = {-500, -200, -200, -200, -200, -200, -200, -500,
                             -200, -100, -100, -100, -100, -100, -100, -200,
                             -100,    0,   80,   80,   80,   80,    0, -100,
                             -100,    0,   80,   80,   80,   80,    0, -100,
                             -100,    0,   50,   80,   80,   50,    0, -100,
                             -100,    0,   50,   50,   50,   50,    0, -100,
                             -100,  -50,    0,    0,    0,    0,  -50, -100,
                             -300, -100, -100, -100, -100, -100, -100, -300};

  int  bishop_value_w[64] = {-200, -100, -100, -100, -100, -100, -100, -200,
                             -100,    0,    0,    0,    0,    0,    0, -100,
                              -25,    0,   40,   40,   40,   40,    0,  -25,
                              -25,    0,   40,   80,   80,   40,    0,  -25,
                                0,    0,   40,   80,   80,   40,    0,    0,
                                0,    0,   40,   40,   40,   40,    0,    0,
                                0,    0,    0,    0,    0,    0,    0,    0,
                                0,    0,    0,    0,    0,    0,    0,    0};

  int  bishop_value_b[64] = { 
                                0,    0,    0,    0,    0,    0,    0,    0,
                                0,    0,    0,    0,    0,    0,    0,    0,
                                0,    0,   40,   40,   40,   40,    0,    0,
                                0,    0,   40,   80,   80,   40,    0,    0,
                              -25,    0,   40,   80,   80,   40,    0,  -25,
                              -25,    0,   40,   40,   40,   40,    0,  -25,
                             -100,    0,    0,    0,    0,    0,    0, -100,
                             -200, -100, -100, -100, -100, -100, -100, -200};
 
  int    rook_value_w[64] = {   0,   20,   40,   60,   60,   40,   20,    0,
                             -100, -100,   40,   60,   60,   40, -100, -100,
                             -100, -100,   40,   60,   60,   40, -100, -100,
                             -100, -100,   40,   60,   60,   40, -100, -100,
                             -100, -100,   40,   60,   60,   40, -100, -100,
                             -100, -100,   40,   60,   60,   40, -100, -100,
                                0,   20,   40,   60,   60,   40,   20,    0,
                                0,   20,   40,   60,   60,   40,   20,    0};
 
  int    rook_value_b[64] = {   0,   20,   40,   60,   60,   40,   20,    0,
                                0,   20,   40,   60,   60,   40,   20,    0,
                             -100, -100,   40,   60,   60,   40, -100, -100,
                             -100, -100,   40,   60,   60,   40, -100, -100,
                             -100, -100,   40,   60,   60,   40, -100, -100,
                             -100, -100,   40,   60,   60,   40, -100, -100,
                             -100, -100,   40,   60,   60,   40, -100, -100,
                                0,   20,   40,   60,   60,   40,   20,    0};

  int   queen_value_w[64] = {-150,  -50, -30, -30, -30, -30, -30, -100,
                             -150, -100,   0,   0,   0,   0,   0, -100,
                             -150, -110,  30,  30,  30,  30,   0, -100,
                             -160, -120,  30,  60,  60,  30,   0, -100,
                             -170, -130,  30,  60,  60,  30,   0, -100,
                             -180, -140,  30,  30,  30,  30,   0, -100,
                             -190, -150,   0,   0,   0,   0,   0, -100,
                             -200, -160, -30, -30, -30, -30, -30, -100};
 
  int   queen_value_b[64] = {-200, -160, -30, -30, -30, -30, -30, -100,
                             -190, -150,   0,   0,   0,   0,   0, -100,
                             -180, -140,  30,  30,  30,  30,   0, -100,
                             -170, -130,  30,  60,  60,  30,   0, -100,
                             -160, -120,  30,  60,  60,  30,   0, -100,
                             -150, -110,  30,  30,  30,  30,   0, -100,
                             -150, -100,   0,   0,   0,   0,   0, -100,
                             -150,  -50, -30, -30, -30, -30, -30, -100};

  int    king_value_w[64] = {-300,-200,-100,-100,-100,-100,-200,-300,
                             -300,-200, -50, -50, -50, -50,-200,-300,
                             -300,-200,   0, 100, 100,   0,-200,-300,
                             -300,-200, 100, 200, 200, 100,-200,-300,
                             -300,-200, 300, 300, 300, 300,-200,-300,
                             -300,-200, 400, 400, 400, 400,-200,-300,
                             -300,-200, 150, 150, 150, 150,-200,-300,
                             -300,-300,-100,-100,-100,-100,-300,-300};

  int    king_value_b[64] = {-300,-300,-100,-100,-100,-100,-300,-300,
                             -300,-200, 150, 150, 150, 150,-200,-300,
                             -300,-200, 400, 400, 400, 400,-200,-300,
                             -300,-200, 300, 300, 300, 300,-200,-300,
                             -300,-200, 100, 200, 200, 100,-200,-300,
                             -300,-200,   0, 100, 100,   0,-200,-300,
                             -300,-200, -50, -50, -50, -50,-200,-300,
                             -300,-200,-100,-100,-100,-100,-200,-300};

   char king_defects_w[64]= { 4, 1, 3, 6, 6, 3, 0, 4,
                              5, 2, 5, 7, 7, 5, 1, 3,
                              6, 4, 6, 7, 7, 6, 4, 6,
                              8, 5, 6, 8, 8, 6, 5, 8,
                              8, 5, 6, 8, 8, 6, 5, 8,
                              8, 5, 6, 8, 8, 6, 5, 8,
                              8, 5, 6, 8, 8, 6, 5, 8,
                              8, 5, 6, 8, 8, 6, 5, 8};

   char king_defects_b[64]= { 8, 5, 6, 8, 8, 6, 5, 8,
                              8, 5, 6, 8, 8, 6, 5, 8,
                              8, 5, 6, 8, 8, 6, 5, 8,
                              8, 5, 6, 8, 8, 6, 5, 8,
                              8, 5, 6, 8, 8, 6, 5, 8,
                              6, 4, 6, 7, 7, 6, 4, 6,
                              5, 2, 5, 7, 7, 5, 1, 3,
                              4, 1, 3, 6, 6, 3, 0, 4};

   char is_corner[64] =      {1, 0, 0, 0, 0, 0, 0, 1,
                              0, 0, 0, 0, 0, 0, 0, 0,
                              0, 0, 0, 0, 0, 0, 0, 0,
                              0, 0, 0, 0, 0, 0, 0, 0,
                              0, 0, 0, 0, 0, 0, 0, 0,
                              0, 0, 0, 0, 0, 0, 0, 0,
                              0, 0, 0, 0, 0, 0, 0, 0,
                              1, 0, 0, 0, 0, 0, 0, 1};

   int flight_sq[64][2] = {{10,17},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{13,22},
                           {0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
                           {0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
                           {0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
                           {0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
                           {0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
                           {0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
                           {41,50},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{46,53}};

  int       p_values[15] =       {QUEEN_VALUE,ROOK_VALUE,BISHOP_VALUE,0,
                                      KING_VALUE,KNIGHT_VALUE,PAWN_VALUE,
                                      0,PAWN_VALUE,KNIGHT_VALUE,KING_VALUE,
                                      0, BISHOP_VALUE,ROOK_VALUE,QUEEN_VALUE};

  int       pawn_rams[9] =           {0,0,PAWN_RAM*2,PAWN_RAM*3,
                                      PAWN_RAM*5,PAWN_RAM*7,PAWN_RAM*13,
                                      PAWN_RAM*15,PAWN_RAM*18};
  int       pawns_isolated[9] =      { 0,PAWN_ISOLATED, 3*PAWN_ISOLATED,
                                       5*PAWN_ISOLATED,8*PAWN_ISOLATED,
                                      10*PAWN_ISOLATED,12*PAWN_ISOLATED,
                                      14*PAWN_ISOLATED,16*PAWN_ISOLATED};

