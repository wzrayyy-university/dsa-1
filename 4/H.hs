import qualified Data.ByteString.Char8 as BS
import Data.Maybe (listToMaybe, catMaybes)

readInteger :: BS.ByteString -> Maybe Integer
readInteger bs = case BS.readInteger bs of
    Just (x, _) -> Just x
    Nothing     -> Nothing

main :: IO ()
main = do
    input <- BS.getContents
    let numbers = catMaybes (map readInteger (tail (BS.lines input)))
        total = sum numbers
    print total