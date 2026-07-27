%Sample Program to sweep the cyclic prefix length (from 0 to 100 symbols)

clearvars; close all;
color{1} = '#233ce6';
color{2} = '#ff5757';

plot_vec = 0 : 2 : 100; 
ber_results = zeros(size(plot_vec));

for it = 1 : length(plot_vec)
    %% Parameters           
    n_subcarriers = 128;                                                        %Max bits for transmission = 2560 4-bit-symbols (with pilot bits) 
    n_symbols = 20;                                                             %Number of symbols
    scs = 15e3;
    data_order = 16;                                                            %QAM order (8bit) --> use 2 symbols to encode a 8-bit character
    pilot_order = 4;                                                            %...
    cp_length = it;
    pilot_sc_loc = 4;                                            
    pilot_sym_loc = 4;
    data{1} = 'I love Mobile Communication ';
    data{2} = 'abcdefghijklmnopqrstuvwxyz '; 
    
    %% Data & Pilot Location mapping
    pilot_locations{1} = false(n_subcarriers, n_symbols);                       %Pilot location 1: carrier(r) / sym(c) = 1 5 9 13 17 21 ...
    pilot_locations{1}(1 : pilot_sym_loc : end, 1 : pilot_sc_loc : end) = true;
    
    pilot_locations{2} = false(n_subcarriers, n_symbols);                       %Pilot location 2: carrier(r) / sym(c) = 3 7 11 15 ...
    pilot_locations{2}(pilot_sc_loc / 2 + 1 : pilot_sc_loc : end, ...
        1 : pilot_sym_loc : end) = true;
    
    data_locations = true(n_subcarriers, n_symbols);
    data_locations(pilot_locations{1} | pilot_locations{2}) = false;            %Max data capacity = sum(sum(data_locations))           
    
    %% Create QAM Symbols
    n_ports = 2;                                                                %Number of transmit antennas (2tx - 2rx)
    data_bits = cell(1, n_ports);                                               %
    data_states = cell(1, n_ports);                                             %Create 1 x 2 cells
    pilot_states = cell(1, n_ports);                                            %
    
    for p = 1 : n_ports
        bitstream = text2bits(data{p});                                         %Converts data string --> Ascii number ---> 8bit-binary --> bitstream
        data_bits{p} = repeat_bits(bitstream, data_order, ...                   %Add pading for QAM --> data_bits (2 symbols for 1 character)
            sum(sum(data_locations)));                                          % calculate the total data locations --> repeat bitstream to fill length --> arrange bits so that 1 symbol = 1 col
                                 
        data_states{p} = qammod(data_bits{p}, data_order, 'gray', ...           % data_state = QAM mod of data_bits (map 8-bit values to complex plane)
            'InputType', 'bit', 'UnitAveragePower', true);
    
        pilot_symbols = randi(pilot_order, n_subcarriers / pilot_sc_loc, ...    % Generate a random pilot symbol
            n_symbols / pilot_sym_loc) - 1;
        pilot_states{p} = qammod(pilot_symbols, pilot_order, 'gray', ...        % QAM mod the pilot signal
            'UnitAveragePower', true);
    end
    
    %% OFDM Modulation 
    tx_grid = cell(1, n_ports);
    tx_signal = cell(1, n_ports);
    for p = 1 : n_ports
        tx_grid{p} = zeros(n_subcarriers, n_symbols);
        tx_grid{p}(data_locations) = data_states{p};                            % Map the data to its location (rows = sub | col = sym)
        tx_grid{p}(pilot_locations{p}) = pilot_states{p};                       % Map the pilot symbol to their location (tx1 and tx2 are different) column-to-column
        
        % Use the pre-built function from the communication toolbox
        %   tx_signal{p} = ofdmmod(tx_grid{p}, n_subcarriers, cp_length);
        
        % Manual OFDM
        k = (0 : n_subcarriers - 1).';                                          % ".'" --> transpose (n x 1 matrix)
        n = (0 : n_subcarriers - 1);                                            % (1 x n matrix) 
    
        dft_matrix = exp(-2i * pi / n_subcarriers * k * n);                     % Original forward DFT matrix - sqrt division moved to the idft - RX (e^-2ipi/n * orthogonal_val * time)
        idft_matrix = dft_matrix' / n_subcarriers;                              % subcarriers no. division for normalization - TX
                                                                                % k(Rows): The distinct Frequencies (0 Hz, 15 kHz, 30 kHz...) | n (Columns): The distinct Time Steps (Sample 0, Sample 1, Sample 2...).
    
        %Manual fftshift (1dim)
        ofdm_grid_shifted = [                                                    % Swap the bottom half with the top half FOR EACH SUBCARRIER (COLUMN)
        tx_grid{p}(n_subcarriers / 2 + 1 : end, :); ...                          % Perform 1D FFTSHIFT for the subcarriers (frequency)
        tx_grid{p}(1 : n_subcarriers / 2, :)];
    
        ofdm_signal_idft = idft_matrix * ofdm_grid_shifted;                     
        cp_segment = ofdm_signal_idft(end-cp_length+1:end, :);
        tx_signal{p} = [cp_segment;ofdm_signal_idft];
        tx_signal{p} = reshape(tx_signal{p}, [], 1);                            % Resize the marix(sub x sym) to dimension (auto) x 1 = (sub*sym) x 1
    
%         figure;
%         plot(real(tx_grid{p}(data_locations)), ...
%             imag(tx_grid{p}(data_locations)), 'o', 'Color', color{p});
%         axlim = max(max(abs(tx_grid{p}))) + 0.05;
%         ylim([-axlim, axlim]); xlim([-axlim, axlim]); axis square;
%         xlabel("In-phase"); ylabel("Quadrature");
%         title('QAM constellation of the Signal');
    end
    
    %% Transmission channel simulation
    fs = n_subcarriers * scs;                                                   % Sampling frequency
    mimoChan = comm.MIMOChannel('SampleRate', fs, ...
        'PathDelays', [0 1.5e-6], ...
        'AveragePathGains', [0 -5], ...
        'MaximumDopplerShift', 20, ...
        'SpatialCorrelationSpecification', 'None', ...
        'NumTransmitAntennas', 2, ...
        'NumReceiveAntennas', 2, ...
        'RandomStream', 'mt19937ar with seed', ...
        'Seed', 12);
    rx_signal = mimoChan([tx_signal{1}, tx_signal{2}]);                         % Transmission simulation
                                                                                % matrix with 2 col --> 2 rx signal
    
    %% OFDM Demodulation                                                        
    rx_grid = cell(1, n_ports); 
    for p = 1 : n_ports                                                         % Loop through individual receivers
         rx_it = reshape(rx_signal(:, p), [], n_symbols);                       % Reshape the output signal
         rx_it = rx_it(cp_length+1:end, :);                                     % Trim out the cyclic prefix 
         rx_it = dft_matrix * rx_it;
    
         rx_grid{p} = [                                                         % Rearrange the signal
         rx_it(n_subcarriers / 2 + 1 : end, :); ...                          
         rx_it(1 : n_subcarriers / 2, :)];
    
    
%         figure;
%         plot(real(rx_grid{p}(data_locations)), ...
%             imag(rx_grid{p}(data_locations)), 'o', 'Color', color{p});
%         axlim = max(max(abs(rx_grid{p}))) + 0.05;
%         ylim([-axlim, axlim]); xlim([-axlim, axlim]); axis square;
%         xlabel("In-phase"); ylabel("Quadrature");
%         title('Received signal');
    end
    
    %% Channel Estimation
    hest = cell(n_ports, n_ports);                                              %estimated channel response matrix
    [X{1}, Y{1}] = meshgrid(1 : pilot_sym_loc : n_symbols, ...                  % Meshgrid of pilot tx1
        1 : pilot_sc_loc : n_subcarriers);
    [X{2}, Y{2}] = meshgrid(1 : pilot_sym_loc : n_symbols, ...                  % Meshgrid of pilot tx2
        1 + pilot_sc_loc / 2 : pilot_sc_loc : n_subcarriers);
    [Xq, Yq] = meshgrid(1 : n_symbols, 1 : n_subcarriers);
    for p_tx = 1 : n_ports
        for p_rx = 1 : n_ports
            hest_pilots = reshape(rx_grid{p_rx}(pilot_locations{p_tx}), ...     %Pull out the pilot symbols
                n_subcarriers / pilot_sc_loc, n_symbols / pilot_sym_loc) ...
                ./ pilot_states{p_tx};
            hest{p_tx}{p_rx} = interp2(X{p_tx}, Y{p_tx}, hest_pilots, ...       %2D interpolation for each tx-rx pair (require)
                Xq, Yq, "spline");
        end
    end
    
    %% Equalize Data                                                            Zero-forcing eq used
    est_grid = zeros(n_subcarriers, n_symbols, 2);                              % Creates a (sub x sym x 2) matrix              
    for k = 1 : n_subcarriers
        for t = 1 : n_symbols
            H = [                                                               % Build a 2x2 matrix that represents every tx-rx pairs of sym t at sub k
                hest{1}{1}(k, t), hest{2}{1}(k, t);
                hest{1}{2}(k, t), hest{2}{2}(k, t)
            ];
            y = [rx_grid{1}(k, t); rx_grid{2}(k, t)];                           % Get 2 rx values at sym t sub k                       
            est_grid(k, t, :) = pinv(H) * y;                                    % estimation of x = H^(-1)*y (pseudo inv used)
        end
    end
    
%     for p = 1 : n_ports                 
%         figure;
%         plot(real(est_grid(:, :, p)), imag(est_grid(:, :, p)), ...
%             'o', 'Color', color{p});
%         axlim = max(max(abs(est_grid(:, :, p)))) + 0.05;
%         ylim([-axlim, axlim]); xlim([-axlim axlim]); axis square;
%         xlabel("In-phase"); ylabel("Quadrature");
%         title('Received signal after Channel Estimation');
%     end
    
    %% QAM Demodulation
%     for p = 1 : n_ports
      for p = 1 : 1
        data_states_rx = est_grid(:, :, p);
        data_states_rx = data_states_rx(data_locations);                        %Extract data from data_location sub by sub --> store in vector 
        data_bits_rx = qamdemod(data_states_rx, data_order, "gray", ...         % de-QAM
            "OutputType", "bit", "UnitAveragePower", true);
        data_rx = bits2text(data_bits_rx);                                      %convert back to string
        n_errors = sum(data_bits_rx ~= data_bits{p}(:));
        BER = n_errors / length(data_bits_rx);
    
%         disp("frequency = " + it*100);
%         disp("Port " + p);
        disp(" BER: " + BER);
        disp(" Data: " + data_rx);
        ber_results(it) = BER;
    end
end
figure;
plot(plot_vec, ber_results, '-o', 'LineWidth', 2, 'Color', '#233ce6');
grid on;
xlabel('Cyclic Prefix (sym)');
ylabel('Bit Error Rate (BER)');

%------------------------------------------------------------------------------------------------------------------------------------------------------

%%Function definitions
%Convert a string of characters to a string of bits
%representing the ASCII value of each characters
function [bits] = text2bits(text)
    ascii_values = double(text);
    binary_str = dec2bin(ascii_values, 8);                                  % return the binary number of min length 8
    bits = reshape(binary_str', 1, []);
    bits = bits - '0';
end

%Convert bit string to text string
function [text] = bits2text(bits)
    binary_vector = bits(:)';
    padLength = mod(-numel(binary_vector), 8);
    binary_vector = [binary_vector, zeros(1, padLength)];
    binary_matrix = reshape(binary_vector, 8, [])';
    decimals = bin2dec(char(binary_matrix + '0'));

    text = char(decimals)';
    text = strip(text, char(0));
end

%Symbol padding
function [bits] = repeat_bits(bitstream, order, n_symbols)
    bits_per_symbol = log2(order);                                          % No. bits for each QAM constellation symbol
    n_bits = bits_per_symbol * n_symbols;                                   % Total no. bits
    factor = ceil(n_bits / length(bitstream));

    bits = repmat(bitstream, 1, factor);                                    % Repeat the matrix to be of size 1 x factor
    bits = bits(1 : n_bits);                                                % Trimming and reshaping to exact length
    bits = reshape(bits, bits_per_symbol, []);          
end