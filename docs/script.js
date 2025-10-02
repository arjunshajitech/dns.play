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

         fetch('https://api.github.com/repos/arjunshajitech/dns.play')
        .then(response => response.json())
        .then(data => {
        const stars = data.stargazers_count;
        document.getElementById('github-star-count').innerText = `Star on GitHub (${stars}) `;
    })
    .catch(error => {
      console.error('Error fetching star count:', error);
      document.getElementById('github-star-count').innerText = 'Star on GitHub';
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