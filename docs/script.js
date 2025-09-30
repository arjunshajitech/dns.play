async function loadCommands() {
    try {
        const res = await fetch('commands.json');
        const commands = await res.json();

        const container = document.getElementById('commands-container');
        commands.forEach(cmd => {
            const div = document.createElement('div');
            div.className = 'command';
            div.innerHTML = `
                    <div class="command-name">${cmd.name}</div>
                    <div class="command-desc">${cmd.desc}</div>
                    <div class="command-code" onclick="copyToClipboard('${cmd.code}')">${cmd.code}</div>
                    `;
            container.appendChild(div);
        });
    } catch (err) {
        console.error('Error loading commands:', err);
    }
}

function copyToClipboard(text) {
    navigator.clipboard.writeText(text).then(() => {
    }).catch(err => {
        console.error('Failed to copy: ', err);
    });
}

loadCommands();