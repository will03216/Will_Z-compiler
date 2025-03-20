#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "ast_direct_declarator.hpp"
#include "ast_function.hpp"
#include "ast_identifier.hpp"
#include "ast_jump_statement.hpp"
#include "ast_node.hpp"
#include "ast_type_specifier.hpp"
#include "ast_constant.hpp"
#include "ast_context.hpp"
#include "ast_variable.hpp"
#include "ast_init_declarator.hpp"
#include "ast_arithmetic_operation.hpp"
#include "ast_compound_statement.hpp"
#include "ast_logic_operation.hpp"
#include "ast_selection_statement.hpp"
#include "ast_iteration_statement.hpp"
#include "ast_argument_list.hpp"
#include "ast_bitwise_operation.hpp"
# include "ast_type_specifier.hpp"
#include "ast_pointers.hpp"
#include "ast_size.hpp"
#include "ast_string.hpp"
#include "ast_type_node.hpp"
#include "ast_struct.hpp"
ast::NodePtr ParseAST(std::string file_name);
