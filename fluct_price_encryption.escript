#!/usr/bin/env escript

websafe_b64_encode(Bin) ->
    encode_websafe(base64:encode(Bin)).

rand_bytes(N) ->
    binary:part(websafe_b64_encode(crypto:strong_rand_bytes(N)), 0, N).

encode_websafe(Bin) ->
    binary:replace(binary:replace(binary:replace(Bin,
						 <<"+">>, <<"-">>, [global]),
				  <<"/">>, <<"_">>, [global]),
		   <<"=">>, <<".">>, [global]).

price_encode([Key1, Key2, Key3], Iv, Data) ->
    websafe_b64_encode(crypto:block_encrypt(des3_cbf, [Key1, Key2, Key3], Iv, Data)).

main(Texts) ->
    io:format(<<"| \"Orig\" | \"Key1\",\"Key2\",\"Key3\" | \"IV\" | \"Enc\" |~n">>),
    E = fun(Text) ->
    		IV = rand_bytes(8),
    		[Key1, Key2, Key3] = [rand_bytes(8), rand_bytes(8), rand_bytes(8)],
    		io:format(<<"| \"~s\" | \"~s\",\"~s\",\"~s\" | \"~s\" | \"~s\" |~n">>,
			  [Text, Key1, Key2, Key3, IV,
			   price_encode([Key1, Key2, Key3], IV, list_to_binary(Text))])
	end,
    lists:map(E, Texts).
