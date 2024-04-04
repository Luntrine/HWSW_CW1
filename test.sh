make

./steg t images/aar.ppm > processed/aar.ppm
cmp --silent images/aar.ppm processed/aar.ppm || echo "aar.ppm is different"

./steg t images/aaw.ppm > processed/aaw.ppm
cmp --silent images/aaw.ppm processed/aaw.ppm || echo "aaw.ppm is different"

./steg t images/aob.ppm > processed/aob.ppm
cmp --silent images/aob.ppm processed/aob.ppm || echo "aob.ppm is different"

./steg t images/aor.ppm > processed/aor.ppm
cmp --silent images/aor.ppm processed/aor.ppm || echo "aor.ppm is different"

./steg t images/aow.ppm > processed/aow.ppm
cmp --silent images/aow.ppm processed/aow.ppm || echo "aow.ppm is different"


./steg t images/ape.ppm > processed/ape.ppm
# cmp --silent images/ape.ppm processed/ape.ppm || echo "ape.ppm is different"

./steg t images/axb.ppm > processed/axb.ppm
cmp --silent images/axb.ppm processed/axb.ppm || echo "axb.ppm different"

./steg t images/axr.ppm > processed/axr.ppm
cmp --silent images/axr.ppm processed/axr.ppm || echo "axr.ppm is different"

./steg t images/axw.ppm > processed/axw.ppm
cmp --silent images/axw.ppm processed/axw.ppm || echo "axw.ppm is ifferent"


./steg t images/black-comments.ppm > processed/black-commnets.ppm
cmp --silent images/black-comments.ppm processed/black-commnets.ppm || echo "black-comments.ppm is different"

./steg t images/black-p6.ppm > processed/black-p6.ppm
cmp --silent images/black-p6.ppm processed/black-p6.ppm || echo "black-p6.ppm different"

./steg t images/black.ppm > processed/black.ppm
cmp --silent images/black.ppm processed/black.ppm || echo "black.ppm is different"

./steg t images/blackbuck.ascii.ppm > processed/blackbuck.ascii.ppm
# cmp --silent images/blackbuck.ascii.ppm processed/blackbuck.ascii.ppm || echo "blackbuck.ascii.ppm different"

./steg t images/feep.ascii.ppm > processed/feep.ascii.ppm
# cmp --silent images/feep.ascii.ppm processed/fee[].ascii.ppm || echo "feet.ascii.ppm different"

./steg t images/hca.ppm > processed/hca.ppm
cmp --silent images/hca.ppm processed/hca.ppm || echo "hca.ppm is different"

./steg t images/hco.ppm > processed/hco.ppm
cmp --silent images/hco.ppm processed/hco.ppm || echo "hco.ppm is different"

./steg t images/hcx.ppm > processed/hcx.ppm
cmp --silent images/hcx.ppm processed/hcx.ppm || echo "hcw.ppm is different"

./steg t images/home-cat-comments.ppm > processed/home-cat-comments.ppm
# cmp --silent images/home-cat-comments.ppm processed/home-cat-comments.ppm || echo "home-cat-comments.ppm is different"

./steg t images/home-cat-p6.ppm > processed/home-cat-p6.ppm
# cmp --silent images/home-cat-p6.ppm processed/home-cat-p6.ppm || echo "home-cat-p6.ppm is different"

./steg t images/home-cat.ppm > processed/home-cat.ppm
# cmp --silent images/home-cat.ppm processed/home-cat.ppm || echo "home-cat.ppm is different"


./steg t images/pbmlib.ascii.ppm > processed/pbmlib.ascii.ppm
# cmp --silent images/pbmlib.ascii.ppm processed/pbmlib.ascii.ppm || echo "pbmilib.ascii.ppm is different"

./steg t images/red.ppm > processed/red.ppm
cmp --silent images/red.ppm processed/red.ppm || echo "red.ppm is different"

./steg t images/sines.ascii.ppm > processed/sines.ascii.ppm
# cmp --silent images/sines.ascii.ppm processed/sines.ascii.ppm || echo "sines.ascii.ppm is different"

./steg t images/star_field.ascii.ppm > processed/star-field.ascii.ppm
# cmp --silent images/star_field.ascii.ppm processed/star-field.ascii.ppm || echo "star-field.ascii.ppm is different"

./steg t images/white-comments.ppm > processed/white-comments.ppm
cmp --silent images/white-comments.ppm processed/white-comments.ppm || echo "white-comments.ppm is different"

./steg t images/white-p6.ppm > processed/white-p6.ppm
cmp --silent images/white-p6.ppm processed/white-p6.ppm || echo "white-p6.ppm is different"

./steg t images/white.ppm > processed/white.ppm
cmp --silent images/white.ppm processed/white.ppm || echo "white.ppm is different"

