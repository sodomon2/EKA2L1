/*
 * Copyright (c) 2021 EKA2L1 Team.
 *
 * This file is part of EKA2L1 project.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <cpu/12l1r/common.h>
#include <cpu/12l1r/arm_visitor.h>
#include <cpu/12l1r/block_gen.h>
#include <cpu/12l1r/visit_session.h>

namespace eka2l1::arm::r12l1 {
    bool arm_translate_visitor::arm_MOV_imm(common::cc_flags cond, bool S, reg_index d, int rotate, std::uint8_t imm8) {
        session_->set_cond(cond);

        common::armgen::arm_reg dest_real = reg_index_to_gpr(d);

        if (dest_real == common::armgen::R15) {
            LOG_TRACE(CPU_12L1R, "Undefined behaviour mov to r15, todo!");
            session_->emit_undefined_instruction_handler();

            return false;
        }

        const common::armgen::arm_reg dest_mapped = session_->reg_supplier_.map(dest_real,
                ALLOCATE_FLAG_DIRTY);

        common::armgen::operand2 imm_op(imm8, static_cast<std::uint8_t>(rotate));

        if (S) {
            session_->big_block_->MOVS(dest_mapped, imm_op);
        } else {
            session_->big_block_->MOV(dest_mapped, imm_op);
        }

        return true;
    }

    bool arm_translate_visitor::arm_MOV_reg(common::cc_flags cond, bool S, reg_index d, std::uint8_t imm5,
                     common::armgen::shift_type shift, reg_index m) {
        session_->set_cond(cond);

        common::armgen::arm_reg dest_real = reg_index_to_gpr(d);
        common::armgen::arm_reg source_real = reg_index_to_gpr(m);

        if (dest_real == common::armgen::R15) {
            LOG_TRACE(CPU_12L1R, "Undefined behaviour mov to r15, todo!");
            session_->emit_undefined_instruction_handler();

            return false;
        }

        const common::armgen::arm_reg dest_mapped = session_->reg_supplier_.map(dest_real,
                ALLOCATE_FLAG_DIRTY);

        const common::armgen::arm_reg source_mapped = session_->reg_supplier_.map(source_real,
                0);

        common::armgen::operand2 imm_op(source_mapped, shift, imm5);

        if (S) {
            session_->big_block_->MOVS(dest_mapped, imm_op);
        } else {
            session_->big_block_->MOV(dest_mapped, imm_op);
        }

        return true;
    }
}