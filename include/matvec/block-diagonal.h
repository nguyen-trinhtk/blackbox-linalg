#pragma once
#include <NTL/mat_ZZ_p.h>
#include <vector>

namespace matvec {
	inline NTL::mat_ZZ_p block_diagonal(const std::vector<NTL::mat_ZZ_p>& blocks) {
		// Compute total size
		std::size_t total = 0;
		for (const auto& B : blocks)
			total += B.NumRows();
		NTL::mat_ZZ_p M;
		M.SetDims(total, total);
		// Fill with zeros
		for (std::size_t i = 0; i < total; ++i)
			for (std::size_t j = 0; j < total; ++j)
				M[i][j] = NTL::ZZ_p(0);
		// Place each block
		std::size_t row_offset = 0, col_offset = 0;
		for (const auto& B : blocks) {
			std::size_t n = B.NumRows();
			for (std::size_t i = 0; i < n; ++i)
				for (std::size_t j = 0; j < n; ++j)
					M[row_offset + i][col_offset + j] = B[i][j];
			row_offset += n;
			col_offset += n;
		}
		return M;
	}
}
