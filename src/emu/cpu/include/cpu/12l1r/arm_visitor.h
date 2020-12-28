/*
 * Copyright (c) 2020 EKA2L1 Team.
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

#pragma once

#include <cpu/12l1r/common.h>
#include <common/armemitter.h>

namespace eka2l1::arm::r12l1 {
    class visit_session;

    class arm_translate_visitor {
    private:
        visit_session *session_;

    public:
        using instruction_return_type = bool;

        explicit arm_translate_visitor(visit_session *session);

        bool arm_MOV_imm(common::cc_flags cond, bool S, reg_index d, int rotate, std::uint8_t imm8);
        bool arm_MOV_reg(common::cc_flags cond, bool S, reg_index d, std::uint8_t imm5,
                common::armgen::shift_type shift, reg_index m);

        bool arm_BL(common::cc_flags cond, std::uint32_t imm24);

        bool arm_LDM(common::cc_flags cond, bool W, reg_index n, reg_list list);
        bool arm_LDMDA(common::cc_flags cond, bool W, reg_index n, reg_list list);
        bool arm_LDMDB(common::cc_flags cond, bool W, reg_index n, reg_list list);
        bool arm_LDMIB(common::cc_flags cond, bool W, reg_index n, reg_list list);
        bool arm_STM(common::cc_flags cond, bool W, reg_index n, reg_list list);
        bool arm_STMDA(common::cc_flags cond, bool W, reg_index n, reg_list list);
        bool arm_STMDB(common::cc_flags cond, bool W, reg_index n, reg_list list);
        bool arm_STMIB(common::cc_flags cond, bool W, reg_index n, reg_list list);

        bool arm_SVC(common::cc_flags cond, const std::uint32_t n);
        bool arm_UDF();
    };
}