/* Prototypes of target machine for GNU compiler.  MIPS version.
   Copyright (C) 1989-2016 Free Software Foundation, Inc.
   Contributed by A. Lichnewsky (lich@inria.inria.fr).
   Changed by Michael Meissner	(meissner@osf.org).
   64-bit r4000 support by Ian Lance Taylor (ian@cygnus.com) and
   Brendan Eich (brendan@microunity.com).

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#ifndef GCC_MIPS_PROTOS_H
#define GCC_MIPS_PROTOS_H

/* Describes how a symbol is used.

   SYMBOL_CONTEXT_CALL
       The symbol is used as the target of a call instruction.

   SYMBOL_CONTEXT_LEA
       The symbol is used in a load-address operation.

   SYMBOL_CONTEXT_MEM
       The symbol is used as the address in a MEM.  */
enum mips_symbol_context {
  SYMBOL_CONTEXT_CALL,
  SYMBOL_CONTEXT_LEA,
  SYMBOL_CONTEXT_MEM
};

/* Classifies a SYMBOL_REF, LABEL_REF or UNSPEC address.

   SYMBOL_ABSOLUTE
       The symbol's value will be calculated using absolute relocations,
       such as %hi and %lo.

   SYMBOL_GP_RELATIVE
       The symbol's value will be calculated by adding a 16-bit offset
       from $gp.

   SYMBOL_PC_RELATIVE
       The symbol's value will be calculated using a MIPS16 PC-relative
       calculation.

   SYMBOL_GOT_PAGE_OFST
       The symbol's value will be calculated by loading an address
       from the GOT and then applying a 16-bit offset.

   SYMBOL_GOT_DISP
       The symbol's value will be loaded directly from the GOT.

   SYMBOL_GOTOFF_PAGE
       An UNSPEC wrapper around a SYMBOL_GOT_PAGE_OFST.  It represents the
       offset from _gp of the GOT entry.

   SYMBOL_GOTOFF_DISP
       An UNSPEC wrapper around a SYMBOL_GOT_DISP.  It represents the
       offset from _gp of the symbol's GOT entry.

   SYMBOL_GOTOFF_CALL
       Like SYMBOL_GOTOFF_DISP, but used when calling a global function.
       The GOT entry is allowed to point to a stub rather than to the
       function itself.

   SYMBOL_GOTOFF_LOADGP
       An UNSPEC wrapper around a function's address.  It represents the
       offset of _gp from the start of the function.

   SYMBOL_TLS
       A thread-local symbol.

   SYMBOL_TLSGD
   SYMBOL_TLSLDM
   SYMBOL_DTPREL
   SYMBOL_GOTTPREL
   SYMBOL_TPREL
       UNSPEC wrappers around SYMBOL_TLS, corresponding to the
       thread-local storage relocation operators.

   SYMBOL_64_HIGH
       For a 64-bit symbolic address X, this is the value of
       (%highest(X) << 16) + %higher(X).

   SYMBOL_64_MID
       For a 64-bit symbolic address X, this is the value of
       (%higher(X) << 16) + %hi(X).

   SYMBOL_64_LOW
       For a 64-bit symbolic address X, this is the value of
       (%hi(X) << 16) + %lo(X).

   SYMBOL_HALF
       An UNSPEC wrapper around any kind of address.  It represents the
       low 16 bits of that address.  */
enum mips_symbol_type {
  SYMBOL_ABSOLUTE,
  SYMBOL_GP_RELATIVE,
  SYMBOL_PC_RELATIVE,
  SYMBOL_GOT_PAGE_OFST,
  SYMBOL_GOT_DISP,
  SYMBOL_GOTOFF_PAGE,
  SYMBOL_GOTOFF_DISP,
  SYMBOL_GOTOFF_CALL,
  SYMBOL_GOTOFF_LOADGP,
  SYMBOL_TLS,
  SYMBOL_TLSGD,
  SYMBOL_TLSLDM,
  SYMBOL_DTPREL,
  SYMBOL_GOTTPREL,
  SYMBOL_TPREL,
  SYMBOL_64_HIGH,
  SYMBOL_64_MID,
  SYMBOL_64_LOW,
  SYMBOL_HALF
};
#define NUM_SYMBOL_TYPES (SYMBOL_HALF + 1)

/* Identifiers a style of $gp initialization sequence.

   LOADGP_NONE
	No initialization sequence is needed.

   LOADGP_OLDABI
	The o32 and o64 PIC sequence (the kind traditionally generated
	by .cpload).

   LOADGP_NEWABI
	The n32 and n64 PIC sequence (the kind traditionally generated
	by .cpsetup).

   LOADGP_ABSOLUTE
	The GNU absolute sequence, as generated by loadgp_absolute.

   LOADGP_RTP
	The VxWorks RTP PIC sequence, as generated by loadgp_rtp.  */
enum mips_loadgp_style {
  LOADGP_NONE,
  LOADGP_OLDABI,
  LOADGP_NEWABI,
  LOADGP_ABSOLUTE,
  LOADGP_RTP
};

struct mips16e_save_restore_info;

/* Classifies a type of call.

   MIPS_CALL_NORMAL
	A normal call or call_value pattern.

   MIPS_CALL_SIBCALL
	A sibcall or sibcall_value pattern.

   MIPS_CALL_EPILOGUE
	A call inserted in the epilogue.  */
enum mips_call_type {
  MIPS_CALL_NORMAL,
  MIPS_CALL_SIBCALL,
  MIPS_CALL_EPILOGUE
};

/* Controls the conditions under which certain instructions are split.

   SPLIT_IF_NECESSARY
	Only perform splits that are necessary for correctness
	(because no unsplit version exists).

   SPLIT_FOR_SPEED
	Perform splits that are necessary for correctness or
	beneficial for code speed.

   SPLIT_FOR_SIZE
	Perform splits that are necessary for correctness or
	beneficial for code size.  */
enum mips_split_type {
  SPLIT_IF_NECESSARY,
  SPLIT_FOR_SPEED,
  SPLIT_FOR_SIZE
};

extern bool mips_symbolic_constant_p (rtx, enum mips_symbol_context,
				      enum mips_symbol_type *);
extern int mips_regno_mode_ok_for_base_p (int, machine_mode, bool);
extern bool mips_stack_address_p (rtx, machine_mode);
extern int mips_address_insns (rtx, machine_mode, bool);
extern int mips_const_insns (rtx);
extern int mips_split_const_insns (rtx);
extern int mips_split_128bit_const_insns (rtx);
extern int mips_load_store_insns (rtx, rtx_insn *);
extern int mips_idiv_insns (machine_mode);
extern rtx_insn *mips_emit_move (rtx, rtx);
#ifdef RTX_CODE
extern void mips_emit_binary (enum rtx_code, rtx, rtx, rtx);
#endif
extern rtx mips_pic_base_register (rtx);
extern rtx mips_got_load (rtx, rtx, enum mips_symbol_type);
extern bool mips_split_symbol (rtx, rtx, machine_mode, rtx *);
extern rtx mips_unspec_address (rtx, enum mips_symbol_type);
extern rtx mips_strip_unspec_address (rtx);
extern void mips_move_integer (rtx, rtx, unsigned HOST_WIDE_INT);
extern bool mips_legitimize_move (machine_mode, rtx, rtx);

extern rtx mips_subword (rtx, bool);
extern bool mips_split_move_p (rtx, rtx, enum mips_split_type);
extern void mips_split_move (rtx, rtx, enum mips_split_type);
extern bool mips_split_move_insn_p (rtx, rtx, rtx);
extern void mips_split_move_insn (rtx, rtx, rtx);
extern void mips_split_128bit_move (rtx, rtx);
extern bool mips_split_128bit_move_p (rtx, rtx);
extern void mips_split_msa_copy_d (rtx, rtx, rtx, rtx (*)(rtx, rtx, rtx));
extern void mips_split_msa_insert_d (rtx, rtx, rtx, rtx);
extern void mips_split_msa_fill_d (rtx, rtx);
extern const char *mips_output_move (rtx, rtx, rtx);
extern bool mips_cfun_has_cprestore_slot_p (void);
extern bool mips_cprestore_address_p (rtx, bool);
extern void mips_save_gp_to_cprestore_slot (rtx, rtx, rtx, rtx);
extern void mips_restore_gp_from_cprestore_slot (rtx);
#ifdef RTX_CODE
extern void mips_expand_scc (rtx *);
extern void mips_expand_conditional_branch (rtx *);
extern void mips_expand_vcondv2sf (rtx, rtx, rtx, enum rtx_code, rtx, rtx);
extern void mips_expand_conditional_move (rtx *);
extern void mips_expand_conditional_trap (rtx);
#endif
extern bool mips_use_pic_fn_addr_reg_p (const_rtx);
extern rtx_insn *mips_expand_call (enum mips_call_type, rtx, rtx, rtx, rtx,
				   bool);
extern void mips_split_call (rtx, rtx);
extern bool mips_get_pic_call_symbol (rtx *, int);
extern void mips_set_return_address (rtx, rtx);
extern bool mips_move_by_pieces_p (unsigned HOST_WIDE_INT, unsigned int);
extern bool mips_store_by_pieces_p (unsigned HOST_WIDE_INT, unsigned int);
extern bool mips_expand_block_move (rtx, rtx, rtx, rtx);
extern bool mips16_expand_copy (rtx, rtx, rtx, rtx);
extern void mips_expand_synci_loop (rtx, rtx);

extern void mips_init_cumulative_args (CUMULATIVE_ARGS *, tree);
extern bool mips_pad_arg_upward (machine_mode, const_tree);
extern bool mips_pad_reg_upward (machine_mode, tree);

extern bool mips_expand_ext_as_unaligned_load (rtx, rtx, HOST_WIDE_INT,
					       HOST_WIDE_INT, bool);
extern bool mips_expand_ins_as_unaligned_store (rtx, rtx, HOST_WIDE_INT,
						HOST_WIDE_INT);
extern bool mips_mem_fits_mode_p (machine_mode mode, rtx x);
extern HOST_WIDE_INT mips_debugger_offset (rtx, HOST_WIDE_INT);

extern void mips_push_asm_switch (struct mips_asm_switch *);
extern void mips_pop_asm_switch (struct mips_asm_switch *);
extern void mips_output_external (FILE *, tree, const char *);
extern void mips_output_ascii (FILE *, const char *, size_t);
extern const char *mips_output_tls_reloc_directive (rtx *);
extern void mips_output_aligned_decl_common (FILE *, tree, const char *,
					     unsigned HOST_WIDE_INT,
					     unsigned int);
extern void mips_declare_common_object (FILE *, const char *,
					const char *, unsigned HOST_WIDE_INT,
					unsigned int, bool);
extern void mips_declare_object (FILE *, const char *, const char *,
				 const char *, ...) ATTRIBUTE_PRINTF_4;
extern void mips_declare_object_name (FILE *, const char *, tree);
extern void mips_finish_declare_object (FILE *, tree, int, int);
extern void mips_set_text_contents_type (FILE *, const char *,
					 unsigned HOST_WIDE_INT, bool);

extern bool mips_small_data_pattern_p (rtx);
extern rtx mips_rewrite_small_data (rtx);
extern HOST_WIDE_INT mips_initial_elimination_offset (int, int);
extern rtx mips_return_addr (int, rtx);
extern bool mips_must_initialize_gp_p (void);
extern enum mips_loadgp_style mips_current_loadgp_style (void);
extern void mips_emit_save_slot_move (rtx, rtx, rtx);
extern void mips_expand_prologue (void);
extern void mips_expand_before_return (void);
extern void mips_expand_epilogue (bool);
extern bool mips_can_use_return_insn (void);

extern bool mips_const_vector_same_val_p (rtx, machine_mode);
extern bool mips_const_vector_same_bytes_p (rtx, machine_mode);
extern bool mips_const_vector_same_int_p (rtx, machine_mode, HOST_WIDE_INT,
					  HOST_WIDE_INT);
extern bool mips_const_vector_shuffle_set_p (rtx, machine_mode);
extern bool mips_const_vector_bitimm_set_p (rtx, machine_mode);
extern bool mips_const_vector_bitimm_clr_p (rtx, machine_mode);
extern rtx mips_msa_vec_parallel_const_half (machine_mode, bool);
extern rtx mips_gen_const_int_vector (machine_mode, HOST_WIDE_INT);
extern bool mips_secondary_memory_needed (enum reg_class, enum reg_class,
					  machine_mode);
extern bool mips_cannot_change_mode_class (machine_mode,
					   machine_mode, enum reg_class);
extern bool mips_dangerous_for_la25_p (rtx);
extern bool mips_modes_tieable_p (machine_mode, machine_mode);
extern enum reg_class mips_secondary_reload_class (enum reg_class,
						   machine_mode,
						   rtx, bool);
extern int mips_class_max_nregs (enum reg_class, machine_mode);

extern machine_mode mips_hard_regno_caller_save_mode (unsigned int,
						      unsigned int,
						      machine_mode);
extern int mips_adjust_insn_length (rtx_insn *, int);
extern void mips_output_load_label (rtx);
extern const char *mips_output_conditional_branch (rtx_insn *, rtx *,
						   const char *, const char *);
extern const char *mips_output_order_conditional_branch (rtx_insn *, rtx *,
							 bool);
extern const char *mips_output_equal_conditional_branch (rtx_insn *, rtx *,
							 bool);
extern const char *mips_output_jump (rtx *, int, int, bool);
extern const char *mips_output_sync (void);
extern const char *mips_output_sync_loop (rtx_insn *, rtx *);
extern unsigned int mips_sync_loop_insns (rtx_insn *, rtx *);
extern const char *mips_output_division (const char *, rtx *);
extern const char *mips_msa_output_division (const char *, rtx *);
extern const char *mips_output_probe_stack_range (rtx, rtx);
extern bool mips_hard_regno_rename_ok (unsigned int, unsigned int);
extern unsigned int mips_hard_regno_nregs (int, machine_mode);
extern bool mips_linked_madd_p (rtx_insn *, rtx_insn *);
extern bool mips_store_data_bypass_p (rtx_insn *, rtx_insn *);
extern int mips_dspalu_bypass_p (rtx, rtx);
extern rtx mips_prefetch_cookie (rtx, rtx);

extern const char *current_section_name (void);
extern unsigned int current_section_flags (void);
extern bool mips_use_ins_ext_p (rtx, HOST_WIDE_INT, HOST_WIDE_INT);

extern const char *mips16e_output_save_restore (rtx, HOST_WIDE_INT);
extern bool mips16e_save_restore_pattern_p (rtx, HOST_WIDE_INT,
					    struct mips16e_save_restore_info *);

extern bool mask_low_and_shift_p (machine_mode, rtx, rtx, int);
extern int mask_low_and_shift_len (machine_mode, rtx, rtx);
extern bool and_operands_ok (machine_mode, rtx, rtx);
extern bool mips_fmadd_bypass (rtx_insn *, rtx_insn *);

union mips_gen_fn_ptrs
{
  rtx (*fn_6) (rtx, rtx, rtx, rtx, rtx, rtx);
  rtx (*fn_5) (rtx, rtx, rtx, rtx, rtx);
  rtx (*fn_4) (rtx, rtx, rtx, rtx);
};

extern void mips_expand_atomic_qihi (union mips_gen_fn_ptrs,
				     rtx, rtx, rtx, rtx);

extern void mips_expand_vector_init (rtx, rtx);
extern bool mips_expand_vec_perm_const (rtx op[4]);
extern void mips_expand_vec_unpack (rtx op[2], bool, bool);
extern void mips_expand_vec_reduc (rtx, rtx, rtx (*)(rtx, rtx, rtx));
extern void mips_expand_vec_minmax (rtx, rtx, rtx,
				    rtx (*) (rtx, rtx, rtx), bool);

extern int mips_ldst_scaled_shift (machine_mode);
extern bool mips_signed_immediate_p (unsigned HOST_WIDE_INT, int, int);
extern bool mips_unsigned_immediate_p (unsigned HOST_WIDE_INT, int, int);
extern const char *umips_output_save_restore (bool, rtx);
extern bool umips_save_restore_pattern_p (bool, rtx);
extern bool umips_load_store_pair_p (bool, rtx *);
extern void umips_output_load_store_pair (bool, rtx *);
extern bool umips_movep_target_p (rtx, rtx);
extern bool umips_12bit_offset_address_p (rtx, machine_mode);
extern bool mips_9bit_offset_address_p (rtx, machine_mode);
extern bool lwsp_swsp_address_p (rtx, machine_mode);
extern bool m16_based_address_p (rtx, machine_mode,
			         int (*)(rtx_def*, machine_mode)); 
extern rtx mips_expand_thread_pointer (rtx);
extern void mips16_expand_get_fcsr (rtx);
extern void mips16_expand_set_fcsr (rtx);

extern bool mips_eh_uses (unsigned int);
extern bool mips_epilogue_uses (unsigned int);
extern void mips_final_prescan_insn (rtx_insn *, rtx *, int);
extern int mips_trampoline_code_size (void);
extern void mips_function_profiler (FILE *);
extern bool mips_load_store_bonding_p (rtx *, machine_mode);

typedef rtx (*mulsidi3_gen_fn) (rtx, rtx, rtx);
#ifdef RTX_CODE
extern mulsidi3_gen_fn mips_mulsidi3_gen_fn (enum rtx_code);
#endif

extern void mips_register_frame_header_opt (void);
extern void mips_expand_vec_cond_expr (machine_mode, machine_mode, rtx *);

extern bool mips_bit_clear_p (enum machine_mode, unsigned HOST_WIDE_INT);
extern void mips_bit_clear_info (enum machine_mode, unsigned HOST_WIDE_INT,
				 int *, int *);
#endif /* ! GCC_MIPS_PROTOS_H */
