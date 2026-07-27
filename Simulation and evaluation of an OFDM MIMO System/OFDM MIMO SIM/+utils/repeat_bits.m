function [bits] = repeat_bits(bitstream, order, n_symbols)
    bits_per_symbol = log2(order);                                          % No. bits for each QAM constellation symbol
    n_bits = bits_per_symbol * n_symbols;                                   % Total no. bits
    factor = ceil(n_bits / length(bitstream));

    bits = repmat(bitstream, 1, factor);                                    % Repeat the matrix to be of size 1 x factor
    bits = bits(1 : n_bits);                                                % Trimming and reshaping to exact length
    bits = reshape(bits, bits_per_symbol, []);          
end

